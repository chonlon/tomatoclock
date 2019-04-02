#include "clockmainwidget.h"
#include "lon_widget/titlebar.hpp"

#include "clock_database/clocksql.hpp"
#include "clock_small_window/clocksmallwindow.h"
#include "clock_subwidgets/chartswidget.h"
#include "clock_subwidgets/clockrunningwidget.h"
#include "clock_subwidgets/labelsandtargetswidget.h"
#include "lon_widget/messagebox.hpp"
#include "settingfileoperations.h"
#include "settingwidget.h"
#include "tomatoclocktimer.h"
// PRIVATE
void lon::ClockMainWidget::tomatoSaveToSql(int duringtime, QString &label,
                                           const QString &target) {
    // if enabel break the tomato..
    // duringtime -= timer->timerStaus()->timeleft()->minutes();
    sql_p_->addAFinishedTomato(duringtime, label, target);
}

void lon::ClockMainWidget::saveSettingToFile(lon::ClockOptions options) {
    SettingFileOperations().saveClockOptionToFile(std::move(options));
    if (setting_widget_p_) {
        setting_widget_p_->window()->close();
        delete setting_widget_p_;
        setting_widget_p_ = nullptr;
    }
}

lon::ClockMainWidget::ClockMainWidget(QWidget *parent)
    : lon::Widget(parent)
    , keep_working_(false) {
    sql_p_ = new lon::ClockSql();
    // this->setWindowFlags(Qt::FramelessWindowHint |
    // Qt::WindowMinimizeButtonHint);
    // title_bar_p_ = new lon::TitleBar(this);

    labels_targets_widget_p_ = new lon::LabelsAndTargetsWidget(sql_p_, this);
    clock_running_widget_p_  = nullptr;
    chart_widget_p_          = nullptr;

    timer = nullptr;

    main_layout_ = new QVBoxLayout(this);
    main_layout_->addWidget(labels_targets_widget_p_);
    connect(labels_targets_widget_p_,
            SIGNAL(startClock(const QString &, const QString &)), this,
            SLOT(displayClock(const QString &, const QString &)));
    connect(labels_targets_widget_p_, SIGNAL(changeSetting()), this,
            SLOT(displaySetting()));
    connect(labels_targets_widget_p_, SIGNAL(showChart()), this,
            SLOT(displayChart()));
    this->centerWidget()->setLayout(main_layout_);
    QWidget *temp = new QWidget(this);
    temp->setMaximumHeight(50);
    this->setBottomBar(temp);

    this->enabelSizeGrip();
    // 设置标题栏的背景图.
    this->setTitleBackground(
        new QPixmap(":/all/Res/Img/titlebarbackground.png"));
    // 设置程序背景
    this->setBackground(new QPixmap(":/all/Res/Img/background.png"));
    this->setMinimumSize(1050, 700);
}

 lon::ClockMainWidget::~ClockMainWidget() {
	 delete sql_p_;
     delete labels_targets_widget_p_;
     delete clock_running_widget_p_;
     delete chart_widget_p_;
     delete title_bar_p_;
 }

void lon::ClockMainWidget::displayClock(const QString &label,
                                        const QString &target) {
    if (labels_targets_widget_p_) {
        main_layout_->removeWidget(labels_targets_widget_p_);
        delete labels_targets_widget_p_;
        labels_targets_widget_p_ = nullptr;
    }

    if (!timer) {
        timer = new lon::TomatoClockTimer(this);
        connect(timer, SIGNAL(tomatoFinished()), this, SLOT(clockFinished()));
    }
    timer->start();

    running_clock_label_name_  = label;
    running_clock_target_name_ = target;

    clock_running_widget_p_ = new lon::ClockRunningWidget(
        running_clock_label_name_, running_clock_target_name_);
    clock_running_widget_p_->setTimer(timer);
    main_layout_->addWidget(clock_running_widget_p_);

    connect(clock_running_widget_p_, SIGNAL(clockStoped()), this,
            SLOT(clockFinished()));
    // timer->setDisplayClockPointer(
    //   clock_running_widget_p_->clock_display_widget_p_);
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
    }

    labels_targets_widget_p_ = new lon::LabelsAndTargetsWidget(sql_p_);
    main_layout_->addWidget(labels_targets_widget_p_);
    connect(labels_targets_widget_p_, SIGNAL(startClock(QString, QString)),
            this, SLOT(displayClock(const QString &, const QString &)));
    connect(labels_targets_widget_p_, SIGNAL(changeSetting()), this,
            SLOT(displaySetting()));
    connect(labels_targets_widget_p_, SIGNAL(showChart()), this,
            SLOT(displayChart()));
}

void lon::ClockMainWidget::displayChart() {
    if (labels_targets_widget_p_) {
        main_layout_->removeWidget(labels_targets_widget_p_);
        delete labels_targets_widget_p_;
        labels_targets_widget_p_ = nullptr;
    }
    chart_widget_p_ = new lon::ChartsWidget(sql_p_);
    //# background
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QColor(255, 255, 255, 30)));
    chart_widget_p_->setPalette(palette);
    main_layout_->addWidget(chart_widget_p_);
    connect(chart_widget_p_, SIGNAL(closeButtonClicked()), this,
            SLOT(displayTarget()));
}

void lon::ClockMainWidget::clockFinished() {
    // 在提前结束番茄钟时, 只有已经超过三分钟的才可以被记录.
    auto time_status = timer->timerStaus();
    time_status->clock_options();
    auto passedtime = time_status->clock_options()->work_time()->minutes_ -
                      time_status->timeleft()->minutes();
    if (passedtime > 3)
        tomatoSaveToSql(passedtime, running_clock_label_name_,
                        running_clock_target_name_);
    if (keep_working_) {
    } else {
        lon::MessageBoxWrapper *m =
            new lon::MessageBoxWrapper(QString::fromLocal8Bit("番茄完成"),
                                       QString::fromLocal8Bit("番茄已完成."));
        displayTarget();
    }
}

void lon::ClockMainWidget::displaySetting() {
    setting_widget_p_ = new SettingWidget();
    setting_widget_p_->show();
    connect(setting_widget_p_, SIGNAL(settingChanged(lon::ClockOptions)), this,
            SLOT(saveSettingToFile(lon::ClockOptions)));
}