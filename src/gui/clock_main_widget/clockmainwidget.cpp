#include "clockmainwidget.h"
#include "../lon_widget/titlebar.hpp"

#include "../clock_small_window/clocksmallwindow.h"
#include "../clock_subwidgets/chartswidget.h"
#include "../clock_subwidgets/clockrunningwidget.h"
#include "../clock_subwidgets/labelsandtargetswidget.h"
#include "../lon_widget/menu.hpp"
#include "../lon_widget/messagebox.hpp"
#include "../settingfileoperations.h"
#include "../settingwidget.h"
#include "clock_database/clocksql.hpp"
// fixme 这里的tomatotimer应该移到utility中.
#include "src/utility/tomatoclocktimer.h"

#include <QGridLayout>
#include <QSystemTrayIcon>
// PRIVATE
void lon::ClockMainWidget::tomatoSaveToSql() {
    // if enabel break the tomato..
    // duringtime -= timer->timerStaus()->timeleft()->minutes();
    auto time_status = timer->timerStaus();
    auto passedtime =
        time_status->clock_options()->work_time()->minutes_ - time_status->timeleft()->minutes();
    // 说明当前时间已经全部完成.
    if (passedtime == 0 && time_status->timeleft()->seconds() == 0)
        passedtime = time_status->clock_options()->work_time()->minutes_;
    // 说明终止计时时计时没有超过3分钟.
    if (passedtime > 3)
        sql_p_->addAFinishedTomato(
            passedtime, running_clock_label_name_, running_clock_target_name_);
}

void lon::ClockMainWidget::saveSettingToFile(ClockOptions options) {
    SettingFileOperations().saveClockOptionToFile(std::move(options));
    if (setting_widget_p_) {
        delete setting_widget_p_;
        setting_widget_p_ = nullptr;
    }
}

void lon::ClockMainWidget::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
        case QSystemTrayIcon::Trigger:
            if (!this->isVisible())
                this->window()->show();
            break;
        default:
            break;
    }
}

lon::ClockMainWidget::ClockMainWidget(QWidget* parent)
    : Widget(parent),
      keep_working_(false),
      sql_p_(ClockSql::Get()),
      today_data_p_(new tomato_clock::TodayData(sql_p_->getTodayData())),
      lastweek_data_p_(new tomato_clock::LastWeekData(sql_p_->getLastWeekData())),
      lastmonth_data_p_(new tomato_clock::LastMonthData(sql_p_->getLastMonthData())) {
    // this->setWindowFlags(Qt::FramelessWindowHint |
    // Qt::WindowMinimizeButtonHint);
    // title_bar_p_ = new lon::TitleBar(this);

    QIcon window_icon(":/icon/Icons/tomato.png");

    system_tray_icon_p_ = new QSystemTrayIcon(this);
    system_tray_icon_p_->setIcon(window_icon);
    system_tray_icon_p_->setToolTip(QString{u8"我是番茄哒"});
    system_tray_icon_p_->show();

    close_action_p_ = new QAction(QString{u8"退出番茄钟"}, this);
    about_action_p_ = new QAction(QString{u8"关于"}, this);
    setting_action_p_ = new QAction(QString{u8"设置"}, this);

    menu_p_ = new Menu(this);

    // addAction will take ownship of pointers.
    menu_p_->addAction(about_action_p_);
    menu_p_->addAction(setting_action_p_);
    menu_p_->addSeparator();
    menu_p_->addAction(close_action_p_);

    system_tray_icon_p_->setContextMenu(menu_p_);

    labels_targets_widget_p_ =
        new LabelsAndTargetsWidget(lastweek_data_p_, lastmonth_data_p_, this);
    clock_running_widget_p_ = nullptr;
    chart_widget_p_ = nullptr;

    timer = nullptr;

    main_layout_ = new QVBoxLayout();
    main_layout_->addWidget(labels_targets_widget_p_);
    connect(labels_targets_widget_p_,
            SIGNAL(startClock(const QString&, const QString&)),
            this,
            SLOT(displayClock(const QString&, const QString&)));
    connect(labels_targets_widget_p_, SIGNAL(changeSetting()), this, SLOT(displaySetting()));
    connect(labels_targets_widget_p_, SIGNAL(showChart()), this, SLOT(displayChart()));
    connect(labels_targets_widget_p_, SIGNAL(redrawWidget()), this, SLOT(displayTarget()));
    this->centerWidget()->setLayout(main_layout_);
    QWidget* temp = new QWidget(this);
    temp->setMaximumHeight(50);
    this->setBottomBar(temp);

    this->enabelSizeGrip();
    // 设置标题栏的背景图.
    this->setTitleBackground(new QPixmap(":/all/Res/Img/titlebarbackground.png"));
    // 设置程序背景
    this->setBackground(new QPixmap(":/all/Res/Img/background.png"));
    // this->resize(1050, 700);
    this->setMinimumSize(950, 650);

    this->setWindowIcon(window_icon);
    this->setTitleIcon(window_icon);
    this->setTitle(QString{u8"番茄钟"});

    connect(close_action_p_, &QAction::triggered, this, [this](void) { this->window()->close(); });
    connect(setting_action_p_, &QAction::triggered, this, &ClockMainWidget::displaySetting);

    connect(system_tray_icon_p_,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    Widget::setCloseFunc(std::bind([](QWidget* widget) { widget->window()->hide(); }, this));
}

lon::ClockMainWidget::~ClockMainWidget() {
    delete sql_p_;
    delete labels_targets_widget_p_;
    delete clock_running_widget_p_;
    delete chart_widget_p_;
}

void lon::ClockMainWidget::displayClock(const QString& label, const QString& target) {
    if (labels_targets_widget_p_) {
        main_layout_->removeWidget(labels_targets_widget_p_);
        delete labels_targets_widget_p_;
        labels_targets_widget_p_ = nullptr;
    }

    if (!timer) {
        timer = new TomatoClockTimer(this);
        connect(timer, SIGNAL(tomatoFinished()), this, SLOT(clockFinished()));
    }
    timer->start();

    running_clock_label_name_ = label;
    running_clock_target_name_ = target;

    clock_running_widget_p_ =
        new ClockRunningWidget(running_clock_label_name_, running_clock_target_name_);
    clock_running_widget_p_->setTimer(timer);
    main_layout_->addWidget(clock_running_widget_p_);

    connect(clock_running_widget_p_, SIGNAL(clockStoped()), this, SLOT(clockBreaked()));
}

void lon::ClockMainWidget::displayTarget() {
    // 切换界面时, 操作不会很频繁, 故不保留原界面.
    if (clock_running_widget_p_) {
        main_layout_->removeWidget(clock_running_widget_p_);
        delete clock_running_widget_p_;
        clock_running_widget_p_ = nullptr;
    } else if (chart_widget_p_) {
        main_layout_->removeWidget(chart_widget_p_);
        delete chart_widget_p_;
        chart_widget_p_ = nullptr;
    } else if (labels_targets_widget_p_) {
        main_layout_->removeWidget(labels_targets_widget_p_);
        delete labels_targets_widget_p_;
        labels_targets_widget_p_ = nullptr;
    }

    labels_targets_widget_p_ = new LabelsAndTargetsWidget(lastweek_data_p_, lastmonth_data_p_);
    main_layout_->addWidget(labels_targets_widget_p_);

    // connections
    connect(labels_targets_widget_p_,
            SIGNAL(startClock(QString, QString)),
            this,
            SLOT(displayClock(const QString&, const QString&)));
    connect(labels_targets_widget_p_, SIGNAL(changeSetting()), this, SLOT(displaySetting()));
    connect(labels_targets_widget_p_, SIGNAL(showChart()), this, SLOT(displayChart()));
    connect(labels_targets_widget_p_, SIGNAL(redrawWidget()), this, SLOT(displayTarget()));
}

void lon::ClockMainWidget::displayChart() {
    if (labels_targets_widget_p_) {
        main_layout_->removeWidget(labels_targets_widget_p_);
        delete labels_targets_widget_p_;
        labels_targets_widget_p_ = nullptr;
    }
    chart_widget_p_ = new ChartsWidget(today_data_p_, lastweek_data_p_, lastmonth_data_p_);
    //# background
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QColor(255, 255, 255, 30)));
    chart_widget_p_->setPalette(palette);
    main_layout_->addWidget(chart_widget_p_);
    connect(chart_widget_p_, SIGNAL(closeButtonClicked()), this, SLOT(displayTarget()));
}

void lon::ClockMainWidget::clockFinished() {
    // 在提前结束番茄钟时, 只有已经超过三分钟的才可以被记录.
    tomatoSaveToSql();
    // 是否开启连续工作模式.
    if (timer->timerStaus()->clock_options()->keepWorking()) {
        timer->start();
    } else {
        MessageBoxWrapper* m =
            new MessageBoxWrapper(QString{u8"番茄完成"}, QString{u8"番茄已完成."});
        displayTarget();
    }
}

void lon::ClockMainWidget::clockBreaked() {
    tomatoSaveToSql();
    timer->stop();
    timer->clear();
    MessageBoxWrapper* m =
        new MessageBoxWrapper(QString{u8"番茄中断"}, QString{u8"已中断, 完成数据已储存."});
    displayTarget();
}

void lon::ClockMainWidget::displaySetting() {
    setting_widget_p_ = new SettingWidget();
    setting_widget_p_->show();
    connect(setting_widget_p_,
            SIGNAL(settingChanged(lon::ClockOptions)),
            this,
            SLOT(saveSettingToFile(lon::ClockOptions)));
}
