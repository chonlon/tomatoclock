#include "addtargetwidget.h"
#include "lon_widget/messagebox.hpp"
#include "clock_database/clocksql.hpp"
#include <QComboBox>
#include <QGridLayout>
static const int window_height = 300;
static const int window_width  = 500;

lon::AddTargetWidget::AddTargetWidget(std::list<QString> labels,
	QWidget *          parent /*= nullptr*/)
	: lon::Widget(parent, lon::TitleBar::CLOSE_MIN)
	, sql_(lon::ClockSql::Get()) {
    labels_combobox_p_ = new QComboBox(this);
    lineedit_p_        = new QLineEdit(this);
    label_p_           = new QLabel(this);
    select_label_p_    = new QLabel(this);
    main_layout_p_     = new QGridLayout(this);

    select_label_p_->setText(tr("选择标签 :"));
    label_p_->setText(tr("请输入目标名 :"));
    for (auto label : labels) {
        labels_combobox_p_->addItem(label);
    }

    main_layout_p_->addWidget(select_label_p_, 0, 0, 1, 1);
    main_layout_p_->addWidget(labels_combobox_p_, 0, 1, 1, 2);
    main_layout_p_->addWidget(label_p_, 1, 0, 1, 1);
    main_layout_p_->addWidget(lineedit_p_, 1, 1, 1, 2);

    this->centerWidget()->setLayout(main_layout_p_);
    this->setFixedSize(window_width, window_height);
    connect(this, SIGNAL(okButtonClicked()), this, SLOT(onOkButtonClicked()));
}

void lon::AddTargetWidget::onOkButtonClicked() {
    QString label  = labels_combobox_p_->currentText();
    QString target = lineedit_p_->text();
    if (sql_->targetExists(label, target))
        showMessage("该标签下已存在同名目标, 请重新输入.");
    else {
        emit targetAdded(label, target);
        this->window()->close();
    }
}

void lon::AddTargetWidget::showMessage(const QString &message) {
    new lon::MessageBoxWrapper("", message);
}