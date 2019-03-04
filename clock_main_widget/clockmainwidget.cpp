#include "clockmainwidget.h"

lon::ClockMainWidget::ClockMainWidget(QWidget *parent)
    :QWidget (parent)
{
    list_widget_p_ = new lon::ListWidget(this);

    top_layout_p_ = new QGridLayout(this);
    main_layout_p_ = new QVBoxLayout(this);

    main_layout_p_->addLayout(top_layout_p_);
    main_layout_p_->addWidget(list_widget_p_);
}

