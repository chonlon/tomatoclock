#include "clockrunningwidget.h"

lon::ClockRunningWidget::ClockRunningWidget(QWidget *parent)
    : QWidget(parent)
    , side_width(50) {
    main_layout_p_          = new QHBoxLayout(this);
    center_layout_p_        = new QVBoxLayout(this);
    bottom_button_layout_p_ = new QHBoxLayout(this);
    left_button_layout_p_   = new QVBoxLayout(this);

    volume_button_p_  = new lon::Button(this);
    pause_button_p_   = new lon::Button(this);
    stop_button_p_    = new lon::Button(this);
    history_button_p_ = new lon::Button(this);
    setting_button_p_ = new lon::Button(this);

    history_button_p_->setFixedSize(40, 40);
    setting_button_p_->setFixedSize(40, 40);

    clock_display_widget_p_ = new lon::ClockDisplayWidget(this);

    left_spacer_p_ = new QSpacerItem(side_width, side_width, QSizePolicy::Fixed,
                                     QSizePolicy::Minimum);
    right_spacer_p_ =
        new QSpacerItem(side_width - 5, side_width - 5, QSizePolicy::Minimum,
                        QSizePolicy::Expanding);

    main_layout_p_->setContentsMargins(0, 0, 0, 0);
    center_layout_p_->setContentsMargins(0, 20, 0, 0);
    bottom_button_layout_p_->setContentsMargins(0, 0, 0, 0);
    left_button_layout_p_->setContentsMargins(5, 5, 5, 5);

    bottom_button_layout_p_->addWidget(volume_button_p_);
    bottom_button_layout_p_->addWidget(pause_button_p_);
    bottom_button_layout_p_->addWidget(stop_button_p_);

    left_button_layout_p_->addWidget(history_button_p_);
    left_button_layout_p_->addItem(right_spacer_p_);
    left_button_layout_p_->addWidget(setting_button_p_);

    center_layout_p_->addWidget(clock_display_widget_p_);
    center_layout_p_->addLayout(bottom_button_layout_p_);

    main_layout_p_->addItem(left_spacer_p_);
    main_layout_p_->addLayout(center_layout_p_);
    main_layout_p_->addLayout(left_button_layout_p_);

    this->show();
}

lon::ClockRunningWidget::~ClockRunningWidget() {}