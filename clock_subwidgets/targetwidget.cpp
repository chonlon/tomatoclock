#include "targetwidget.h"
#include <QPainter>
#include <QRect>
#include <QSpacerItem>
static const int label_height = 25;

void lon::TargetWidget::initWidgets() {
    label_p_                  = new QLabel(this);
    target_label_p_           = new QLabel(this);
    start_target_button_p_    = new lon::Button(this);
    complete_target_button_p_ = new lon::Button(this);
    week_label_p_             = nullptr;
    month_label_p_            = nullptr;
    // ����scrollarea �Զ���Ϊ����������ĸ�����,
    // �����������widget�ĸ������н���ı���ɫ��䣬��ô���widget�ǲ��ܹ��Զ���䱳����..������������widget��painter����ʧЧ.
    week_situation_widget_p_  = nullptr;
    month_situation_widget_p_ = nullptr;
    main_layout_p_            = new QGridLayout(this);
}

void lon::TargetWidget::setWidgetsStyle() {
    label_p_->setText(label_name_);
    target_label_p_->setText(target_name_);

    label_p_->setFixedHeight(label_height);
    target_label_p_->setFixedHeight(label_height);

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

    start_target_button_p_->setFixedSize(45, 45);
    start_target_button_p_->setNormal(
        new QIcon(":/icon/Icons/play_normal.png"));
    start_target_button_p_->setFocus(new QIcon(":/icon/Icons/play_focus.png"));
    start_target_button_p_->setPressed(
        new QIcon(":/icon/Icons/play_pressed.png"));
    start_target_button_p_->setFlat(true);
    start_target_button_p_->setStyleSheet("border:none");
	start_target_button_p_->setToolTip(QString::fromLocal8Bit("��ʼ������"));

    complete_target_button_p_->setFixedSize(45, 45);
    complete_target_button_p_->setFlat(true);
    complete_target_button_p_->setStyleSheet("border:none");
	complete_target_button_p_->setScalingFactor(0.6);
	complete_target_button_p_->setNormal(new QIcon(":/icon/Icons/finish.png"));
	complete_target_button_p_->setFocus(new QIcon(":/icon/Icons/finish.png"));
	complete_target_button_p_->setPressed(new QIcon(":/icon/Icons/finish.png"));
	complete_target_button_p_->setToolTip(QString::fromLocal8Bit("Ŀ�������"));
}

void lon::TargetWidget::setThisWidgetStyle() {
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
}

void lon::TargetWidget::initLayout() {
    QSpacerItem *item1 =
        new QSpacerItem(30, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);
    QSpacerItem *item2 =
        new QSpacerItem(30, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);
    main_layout_p_->addItem(item1, 0, 0, 1, 1);
    main_layout_p_->addWidget(label_p_, 0, 1, 1, 1);
    main_layout_p_->addItem(item2, 1, 0, 1, 1);
    main_layout_p_->addWidget(target_label_p_, 1, 1, 1, 1);
    main_layout_p_->addWidget(complete_target_button_p_, 0, 4, 2, 1);
    main_layout_p_->addWidget(start_target_button_p_, 0, 5, 2, 1);
    this->setLayout(main_layout_p_);
}

void lon::TargetWidget::drawWorkStuation(QWidget *widget, int num) {
	qobject_cast<QLabel*>(widget)->setText(QString::number(num));
}

lon::TargetWidget::TargetWidget(QString label_name, QString target_name,
                                QWidget *parent)
    : QWidget(parent)
    , label_name_(label_name)
    , target_name_(target_name) {
    initWidgets();
    setWidgetsStyle();
    initLayout();
    setThisWidgetStyle();
    // qt
    // ��singal��slot�����Ĳ��������һ��(����signal�Ĳ�����ȫ����slot�Ĳ���).
    // connect(start_target_button_p_, SIGNAL(clicked()), this,
    // SIGNAL(startButtonClicked(label_name_, target_name_)));
    connect(start_target_button_p_, SIGNAL(clicked()), this,
            SLOT(emitButtonClicked()));
    connect(complete_target_button_p_, &QPushButton::clicked, this,
            [this]() { emit targetFinished(target_name_); });
}

void lon::TargetWidget::setLastWeekData(
    std::shared_ptr<lon::tomato_clock::LastWeekData> ptr) {
    last_week_data_p_        = ptr;
    week_label_p_            = new QLabel(this);
    week_situation_widget_p_ = new QLabel(this);
    week_label_p_->setFixedHeight(label_height);
    week_label_p_->setText(QString::fromLocal8Bit("��ȥ7��"));
    main_layout_p_->addWidget(week_situation_widget_p_, 0, 2, 1, 1);
    main_layout_p_->addWidget(week_label_p_, 1, 2, 1, 1);
    int count{};
    if (last_week_data_p_ != nullptr)
        for (auto i : (last_week_data_p_->target_data))
            if (i.first == target_name_) count += i.second;
    drawWorkStuation(week_situation_widget_p_, count);
}

void lon::TargetWidget::setLastMonthData(
    std::shared_ptr<lon::tomato_clock::LastMonthData> ptr) {
    last_month_data_p_        = ptr;
    month_label_p_            = new QLabel(this);
    month_situation_widget_p_ = new QLabel(this);
    month_situation_widget_p_->setPalette(QPalette(Qt::red));
    month_situation_widget_p_->setAutoFillBackground(false);
    month_label_p_->setFixedHeight(label_height);
    month_label_p_->setText(QString::fromLocal8Bit("��ȥ30��"));
    main_layout_p_->addWidget(month_situation_widget_p_, 0, 3, 1, 1);
    main_layout_p_->addWidget(month_label_p_, 1, 3, 1, 1);
    int count{};
    if (last_month_data_p_ != nullptr)
        for (auto i : (last_month_data_p_->target_data))
            if (i.first == target_name_) count += i.second;
    drawWorkStuation(month_situation_widget_p_, count);
}