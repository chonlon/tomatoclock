#include "targetwidget.h"

lon::TargetWidget::TargetWidget(QString label_name, QString target_name,
                                QWidget *parent)
    : QWidget(parent)
    , label_name_(label_name)
    , target_name_(target_name) {
    label_p_        = new QLabel(this);
    target_label_p_ = new QLabel(this);
    main_layout_p_  = new QGridLayout(this);

    label_p_->setText(label_name_);
    target_label_p_->setText(target_name_);
    label_p_->setFixedHeight(25);
    target_label_p_->setFixedHeight(25);

    start_target_button_p_ = new lon::Button(this);
    start_target_button_p_->setFixedSize(45, 45);

    // sub_layout_p_->addWidget(target_label_p_);
    // sub_layout_p_->addWidget(label_p_);
    // sub_layout_p_->setContentsMargins(0, 0, 0, 0);
    main_layout_p_->addWidget(label_p_, 0, 0);
    main_layout_p_->addWidget(target_label_p_, 1, 0);

    main_layout_p_->addWidget(start_target_button_p_, 0, 1, 2, 1);
    this->setLayout(main_layout_p_);

    this->setFixedHeight(80);
    this->setMinimumWidth(450);
    this->setMaximumWidth(650);
    // qt
    // 的singal和slot函数的参数必须的一样(或者signal的参数完全包含slot的参数).
    // connect(start_target_button_p_, SIGNAL(clicked()), this,
    // SIGNAL(startButtonClicked(label_name_, target_name_)));
    connect(start_target_button_p_, SIGNAL(clicked()), this,
            SLOT(emitButtonClicked()));
}