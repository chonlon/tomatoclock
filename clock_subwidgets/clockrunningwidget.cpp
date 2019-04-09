#include "clockrunningwidget.h"
#include "lon_widget/button.hpp"
#include "tomatoclocktimer.h"
#include <QLabel>

void lon::ClockRunningWidget::setReceiveTimerWidget(
    lon::DisplayClockBase *displaye_p) {
    current_display_widget_p_ = displaye_p;
}
/// <summary>
/// 每次更新timer都会自动将当前displaywidget与timer关联.
/// </summary>
void lon::ClockRunningWidget::setTimer(lon::TomatoClockTimer *timer) {
    timer_p_ = timer;
    timer_p_->setDisplayClockPointer(current_display_widget_p_);
}

lon::ClockRunningWidget::ClockRunningWidget(const QString label_name,
                                            const QString target_name,
                                            QWidget *     parent)
    : QWidget(parent) {
    main_display_widget_p_ = new lon::ClockDisplayWidget(this);
    main_layout_p_         = new QGridLayout(this);
    main_layout_p_->addWidget(main_display_widget_p_, 0, 0, 1, 2);
    label_label_p_ = new QLabel(this);
    label_label_p_->setText(label_name);
    label_label_p_->setMaximumSize(QSize(16777215, 50));
    QFont font;
    font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
    font.setPointSize(10);
    label_label_p_->setFont(font);
    label_label_p_->setAlignment(Qt::AlignCenter);
    main_layout_p_->addWidget(label_label_p_, 1, 0, 1, 2);
    target_label_p_ = new QLabel(this);
    target_label_p_->setText(target_name);
    target_label_p_->setMaximumSize(QSize(16777215, 50));
    QFont font1;
    font1.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
    font1.setPointSize(8);
    target_label_p_->setFont(font1);
    target_label_p_->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    main_layout_p_->addWidget(target_label_p_, 2, 0, 1, 2);
    stop_button_p_ = new lon::Button(this);
    stop_button_p_->setMaximumSize(QSize(45, 45));
    main_layout_p_->addWidget(stop_button_p_, 3, 0, 1, 1);
    small_window_switch_button_p_ = new lon::Button(this);
    small_window_switch_button_p_->setMaximumSize(QSize(45, 45));
    main_layout_p_->addWidget(small_window_switch_button_p_, 3, 1, 1, 1);

    setReceiveTimerWidget(main_display_widget_p_);

    connect(stop_button_p_, SIGNAL(clicked()), this,
            SLOT(onStopButtonClicked()));
    connect(small_window_switch_button_p_, SIGNAL(clicked()), this,
            SLOT(onSmallWindowButtonClicked()));
    this->show();
}

lon::ClockRunningWidget::~ClockRunningWidget() {}

void lon::ClockRunningWidget::onStopButtonClicked() { emit clockStoped(); }

void lon::ClockRunningWidget::onSmallWindowButtonClicked() {
    this->window()->setVisible(false);
    small_window_p_ = new lon::clock_window::ClockSmallWindow(
        label_label_p_->text(), target_label_p_->text());
    this->setReceiveTimerWidget(small_window_p_->progress_widget_);
    timer_p_->setDisplayClockPointer(current_display_widget_p_);
    small_window_p_->show();
    connect(small_window_p_, SIGNAL(clockStoped()), this,
            SIGNAL(clockStoped()));
    connect(small_window_p_, SIGNAL(smallWindowClosing()), this,
            SLOT(backToCurrentWidget()));
}

void lon::ClockRunningWidget::backToCurrentWidget() {
    this->setReceiveTimerWidget(main_display_widget_p_);
    timer_p_->setDisplayClockPointer(current_display_widget_p_);
    small_window_p_->window()->close();
    delete small_window_p_;
    small_window_p_ = nullptr;
    this->window()->setVisible(true);
}