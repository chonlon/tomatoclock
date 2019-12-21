#include "toolswidget.h"
#include "../lon_widget/button.hpp"

#include <QGridLayout>
#include <QLabel>

void lon::ToolsWidget::onCloseClicked() { this->window()->close(); }

lon::ToolsWidget::ToolsWidget(const QString& label_name,
                              const QString& target_name,
                              QWidget* parent)
    : QWidget(parent) {
    main_layout_ = new QGridLayout(this);
    main_layout_->setContentsMargins(5, 0, 0, 0);
    stop_ = new Button(this);
    stop_->setFixedSize(QSize(45, 45));
    main_layout_->addWidget(stop_, 0, 1, 2, 1);
    label_label_ = new QLabel(this);
    label_label_->setText(label_name);
    QFont font;
    font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
    font.setPointSize(10);
    font.setBold(true);
    font.setWeight(75);
    label_label_->setFont(font);
    label_label_->setAlignment(Qt::AlignCenter);
    main_layout_->addWidget(label_label_, 0, 0, 1, 1);

    close_ = new Button(this);
    close_->setFixedSize(QSize(45, 45));
    close_->setFlat(true);
    close_->setStyleSheet("border:none");
    close_->setNormal(new QIcon(":/icon/Icons/back_normal.png"));
    close_->setFocus(new QIcon(":/icon/Icons/back_focus.png"));
    close_->setPressed(new QIcon(":/icon/Icons/back_pressed.png"));
    stop_->setFlat(true);
    stop_->setStyleSheet("border:none");
    stop_->setNormal(new QIcon(":/icon/Icons/stop_normal.png"));
    stop_->setFocus(new QIcon(":/icon/Icons/stop_focus.png"));
    stop_->setPressed(new QIcon(":/icon/Icons/stop_pressed.png"));

    main_layout_->addWidget(close_, 0, 2, 2, 1);
    target_label_ = new QLabel(this);
    target_label_->setText(target_name);
    QFont font1;
    font1.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
    target_label_->setFont(font1);
    target_label_->setAlignment(Qt::AlignCenter);
    main_layout_->addWidget(target_label_, 1, 0, 1, 1);
    connect(stop_, SIGNAL(clicked()), this, SIGNAL(stopButtonClicked()));
    connect(close_, SIGNAL(clicked()), this, SIGNAL(closeButtonClicked()));
}
