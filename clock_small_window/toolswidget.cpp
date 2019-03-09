#include "toolswidget.h"

void lon::ToolsWidget::onCloseClicked() { this->window()->close(); }

lon::ToolsWidget::ToolsWidget(QWidget *parent)
    : QWidget(parent) {
    tomato_label_           = new QLabel(this);
    main_layout_            = new QHBoxLayout(this);
    window_operation_group_ = new QVBoxLayout(this);

    main_layout_->setContentsMargins(5, 0, 0, 0);
    window_operation_group_->setContentsMargins(0, 0, 0, 0);

    close_   = new lon::Button(this);
    restore_ = new lon::Button(this);
    volume_  = new lon::Button(this);
    stop_    = new lon::Button(this);

    window_operation_group_->addWidget(close_);
    window_operation_group_->addWidget(restore_);
    main_layout_->addWidget(tomato_label_);
    main_layout_->addWidget(stop_);
    main_layout_->addWidget(volume_);
    main_layout_->addLayout(window_operation_group_);

    connect(close_, SIGNAL(clicked(bool)), this, SLOT(onCloseClicked()));
}