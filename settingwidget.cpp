#include "settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent)
    : lon::Widget(parent) {
    widget_p_ = new SettingWidgetPrivate(this);
    this->setCenterWidget(widget_p_);
    this->setBottomBar(nullptr);
    this->setFixedSize(800, 550);
    connect(this, SIGNAL(closeButtonClicked()), this, SLOT(closingWindow()));
}

void SettingWidget::closingWindow() {
    emit settingChanged((std::move(*widget_p_->clockOptionSetted())));
}