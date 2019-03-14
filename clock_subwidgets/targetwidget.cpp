#include "targetwidget.h"

lon::TargetWidget::TargetWidget(QWidget *parent) : QWidget(parent)
{
	QString target_name("target_name_add_later");
	QString label_name("label_name_add_later");
	label_p_ = new QLabel(this);
	target_label_p_ = new QLabel(this);
	main_layout_p_ = new QGridLayout(this);

	label_p_->setText(label_name);
	target_label_p_->setText(target_name);
	label_p_->setFixedHeight(25);
	target_label_p_->setFixedHeight(25);

	start_target_button_p_ = new lon::Button(this);
	start_target_button_p_->setFixedSize(45, 45);

	//sub_layout_p_->addWidget(target_label_p_);
	//sub_layout_p_->addWidget(label_p_);
	//sub_layout_p_->setContentsMargins(0, 0, 0, 0);
	main_layout_p_->addWidget(label_p_, 0, 0);
	main_layout_p_->addWidget(target_label_p_, 1, 0);


	main_layout_p_->addWidget(start_target_button_p_, 0, 1, 2, 1);
	this->setLayout(main_layout_p_);

	this->setFixedHeight(80);
	connect(start_target_button_p_, SLOT(clicked()), this, SIGNAL(startButtonClicked()));
}
