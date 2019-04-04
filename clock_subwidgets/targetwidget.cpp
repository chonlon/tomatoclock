#include "targetwidget.h"

#include <QSpacerItem>
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

    QFont font;
    font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
    font.setPointSize(10);
    font.setBold(true);
    font.setWeight(75);
    label_p_->setFont(font);
    QFont font2;
    font2.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
    font2.setPointSize(8);
    target_label_p_->setFont(font2);

    start_target_button_p_ = new lon::Button(this);
    start_target_button_p_->setFixedSize(45, 45);
	start_target_button_p_->setNormal(new QIcon(":/icon/Icons/play_normal.png"));
	start_target_button_p_->setFocus(new QIcon(":/icon/Icons/play_focus.png"));
	start_target_button_p_->setPressed(new QIcon(":/icon/Icons/play_pressed.png"));
	start_target_button_p_->setFlat(true);
	start_target_button_p_->setStyleSheet("border:none");

    // sub_layout_p_->addWidget(target_label_p_);
    // sub_layout_p_->addWidget(label_p_);
    // sub_layout_p_->setContentsMargins(0, 0, 0, 0);horizontalSpacer_2 = new
    // QSpacerItem(40, 20, );
    QSpacerItem *item1 =
        new QSpacerItem(30, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);
    QSpacerItem *item2 =
        new QSpacerItem(30, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);
    main_layout_p_->addItem(item1, 0, 0, 1, 1);
    main_layout_p_->addWidget(label_p_, 0, 1, 1, 1);
    main_layout_p_->addItem(item2, 1, 0, 1, 1);
    main_layout_p_->addWidget(target_label_p_, 1, 1, 1, 1);

    main_layout_p_->addWidget(start_target_button_p_, 0, 2, 2, 1);
    this->setLayout(main_layout_p_);

    this->setFixedHeight(80);
    this->setMinimumWidth(450);
    this->setMaximumWidth(850);

    this->setAutoFillBackground(true);
    QPixmap  pixmap(":/all/Res/Img/titlebarbackground.png");
    QPalette palette = this->palette();
    palette.setBrush(this->backgroundRole(),
                     QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation)));
    this->setPalette(palette);
    // qt
    // 的singal和slot函数的参数必须的一样(或者signal的参数完全包含slot的参数).
    // connect(start_target_button_p_, SIGNAL(clicked()), this,
    // SIGNAL(startButtonClicked(label_name_, target_name_)));
    connect(start_target_button_p_, SIGNAL(clicked()), this,
            SLOT(emitButtonClicked()));
}