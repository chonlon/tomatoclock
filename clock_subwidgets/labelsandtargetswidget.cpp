#include "labelsandtargetswidget.h"
#include "lon_widget/button.hpp"
#include "lon_widget/listwidget.hpp"
#include "clock_database/clocksql.hpp"
#include "clock_subwidgets/targetwidget.h"

#include <iostream>

static const unsigned int duration = 600000;
static const unsigned int label_widget_height = 100;
static const int button_width_height = 50;

lon::LabelsAndTargetsWidget::LabelsAndTargetsWidget(lon::ClockSql *sql, QWidget *parent) : QWidget(parent),
sql_(sql)
{
    main_layout_p_ = new QVBoxLayout(this);
	// labels ..
    labels_widget_p_ = new QWidget(this);
    labels_layout_p_ = new QGridLayout(labels_widget_p_);
    labels_main_layout_p_ = new QHBoxLayout(labels_widget_p_);
    add_label_button_layout_p_   = new QVBoxLayout(labels_widget_p_);

	add_label_button_p_ = new lon::Button(this);

	labels_widget_p_->setFixedHeight(label_widget_height);
    add_label_button_p_->setFixedSize( button_width_height,
									   button_width_height);
	add_label_button_p_->setToolTip(QString::fromLocal8Bit("添加标签"));

	// 关于layout的addSapcerItem, 文档里面没有写明会获得item指针的所有权, 但事实上是获得了的(写在addItem里面了...).
	// 所以同一个spacer_item不能添加两次.
	// 而且, 在这个类的析构函数中不需要考虑释放spacer_item的内存.
	unsigned int height = (label_widget_height - button_width_height) / 2;
	label_widget_spacer_p_ = new QSpacerItem(
      height , height, QSizePolicy::Minimum , QSizePolicy::Fixed);
	QSpacerItem *item_copy = new QSpacerItem(*label_widget_spacer_p_);


	labels_widget_p_->setLayout(labels_layout_p_);

	add_label_button_layout_p_->addSpacerItem(label_widget_spacer_p_);
    add_label_button_layout_p_->addWidget(add_label_button_p_);
    add_label_button_layout_p_->addSpacerItem(item_copy);

	labels_main_layout_p_->addWidget(labels_widget_p_);
    labels_main_layout_p_->addLayout(add_label_button_layout_p_);
    //labels_main_layout_p_->setAlignment(add_label_button_layout_p_,
    //                                         Qt::AlignRight);


	std::vector<QString> labels_name(sql_->getAllLabels());
	uint8_t row_width = 8;
	uint8_t current_cloumn= 0;
	uint8_t current_row = 0;
	for (auto i : labels_name) {
		QPushButton *button = new QPushButton(labels_widget_p_);
		button->setFixedSize(60, 30);
		button->setText(i);
		button->setToolTip(i);
		labels_layout_p_->addWidget(button, current_row, current_cloumn);
		if (++current_cloumn == row_width) {
			current_cloumn = 0;
			++current_row;
		}
	}

	// targets..
    target_main_layout_p_ = new QHBoxLayout(this);
    target_button_layout_p_ = new QVBoxLayout(this);

	targets_list_widget_p_ = new lon::ListWidget(this);

	target_button_spacer_p_ =
        new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

	add_target_button_p_ = new lon::Button(this);
    history_button_p_    = new lon::Button(this);
	setting_button_p_ = new lon::Button(this);

	add_target_button_p_->setFixedSize(button_width_height,
                                       button_width_height);
	add_target_button_p_->setToolTip(QString::fromLocal8Bit("添加目标"));
    history_button_p_->setFixedSize(button_width_height, button_width_height);
	history_button_p_->setToolTip(QString::fromLocal8Bit("查看历史番茄"));
	setting_button_p_->setFixedSize(button_width_height, button_width_height);
	setting_button_p_->setToolTip(QString::fromLocal8Bit("设置"));

    target_button_layout_p_->addWidget(add_target_button_p_);
    target_button_layout_p_->addWidget(history_button_p_);
    target_button_layout_p_->addSpacerItem(target_button_spacer_p_);
	target_button_layout_p_->addWidget(setting_button_p_);

	target_main_layout_p_->addWidget(targets_list_widget_p_);
    target_main_layout_p_->addLayout(target_button_layout_p_);

	std::vector<QString> targets_name(sql_->getTargetsByLabel(""));
	for (auto i : targets_name) {
		lon::TargetWidget *target_widget = new lon::TargetWidget("test", "test",this);
		targets_list_widget_p_->addWidget(target_widget);
		connect(target_widget, SIGNAL(startButtonClicked(const QString&,const QString&)), this, SIGNAL(startClock(const QString&,const QString&)));
	}

	// set this widget..
    main_layout_p_->addLayout(labels_main_layout_p_);
    main_layout_p_->addLayout(target_main_layout_p_);
    this->setLayout(main_layout_p_);
}

void lon::LabelsAndTargetsWidget::onLabelButtonClicked() {
	lon::Button *button = qobject_cast<lon::Button*> (sender());

	auto iter = button_map_.find(button);
	if((*iter).second->isNull()) {
		QWidget *widget = new QWidget();
		delete iter->second;
		button_map_.erase(iter);
        //button_map_.emplace(std::make_pair(
            //button, lon::AutoDeleteWidgetPointer(duration, widget)));
	}
	// repalce current target list widget with targets belong the clicked label.
}

//void lon::LabelsAndTargetsWidget::startClock(const QString &label_name,const QString &target_name)
//{
//	qDebug() << "-------------" << label_name << "=======" << target_name;
//}

