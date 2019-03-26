#include "settingwidget.h"


SettingWidget::SettingWidget(QWidget *parent) :
    lon::Widget(parent)
{
    widget_p_ = new SettingWidgetPrivate(this);
	this->setCenterWidget(widget_p_);
	this->setBottomBar(nullptr);
	this->setFixedSize(800, 500);
}

void SettingWidget::saveSettingToFile() {
	clock_option_setted_p_ = new lon::ClockOptions(std::move(*widget_p_->clockOptionSetted()));
}
