#include "addtargetwidget.h"
#include <QComboBox>
#include <QGridLayout>
static const int window_height = 300;
static const int window_width = 500;

lon::AddTargetWidget::AddTargetWidget(std::list<QString> labels, std::list<QString> targets, QWidget *parent /*= nullptr*/) : lon::Widget(parent, lon::TitleBar::CLOSE_MIN)
{
	labels_combobox_p_ = new QComboBox(this);
	lineedit_p_ = new QLineEdit(this);
	label_p_ = new QLabel(this);
	select_label_p_ = new QLabel(this);
	main_layout_p_ = new QGridLayout(this);

	select_label_p_->setText(tr("选择标签 :"));
	label_p_->setText(tr("请输入目标名 :"));
	labels.push_front("");
	labels.push_back("1");
	labels.push_back("2");
	for (auto label : labels) {
		labels_combobox_p_->addItem(label);
	}

	main_layout_p_->addWidget(select_label_p_, 0, 0, 1, 1);
	main_layout_p_->addWidget(labels_combobox_p_, 0, 1, 1, 2);
	main_layout_p_->addWidget(label_p_, 1, 0, 1, 1);
	main_layout_p_->addWidget(lineedit_p_, 1, 1, 1, 2);

	this->centerWidget()->setLayout(main_layout_p_);
	this->setFixedSize(window_width, window_height);
}

void lon::AddTargetWidget::onOkButtonClicked()
{

}

void lon::AddTargetWidget::onCancelButtonClicked()
{

}
