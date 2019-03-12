#include "labelsandtargetswidget.h"
static const unsigned int duration = 600000;
static const unsigned int label_widget_height = 100;
static const unsigned int button_width_height = 50;

lon::LabelsAndTargetsWidget::LabelsAndTargetsWidget(QWidget *parent) : QWidget(parent)
{
    main_layout_p_ = new QVBoxLayout(this);
	// labels ..
    labels_widget_p_ = new QWidget(this);
    labels_layout_p_ = new QGridLayout(labels_widget_p_);
    labels_widget_main_layout_p_ = new QHBoxLayout(labels_widget_p_);
    add_label_button_layout_p_   = new QVBoxLayout(labels_widget_p_);

	add_label_button_p_ = new lon::Button(this);

	labels_widget_p_->setFixedHeight(label_widget_height);
    add_label_button_p_->setFixedSize( button_width_height,
									   button_width_height);

	unsigned int height = (label_widget_height - button_width_height) / 2;
	label_widget_spacer_p_ = new QSpacerItem(
      height , height, QSizePolicy::Minimum , QSizePolicy::Fixed);

	labels_widget_p_->setLayout(labels_layout_p_);

	add_label_button_layout_p_->addSpacerItem(label_widget_spacer_p_);
    add_label_button_layout_p_->addWidget(add_label_button_p_);
    add_label_button_layout_p_->addSpacerItem(label_widget_spacer_p_);

	labels_widget_main_layout_p_->addWidget(labels_widget_p_);
    labels_widget_main_layout_p_->addLayout(add_label_button_layout_p_);
    labels_widget_main_layout_p_->setAlignment(add_label_button_layout_p_,
                                               Qt::AlignRight);


	// targets..
    target_main_layout_p_ = new QHBoxLayout(this);
    target_button_layout_p_ = new QVBoxLayout(this);

	targets_list_widget_p_ = new lon::ListWidget(this);

	target_button_spacer_p_ =
        new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

	add_target_button_p_ = new lon::Button(this);
    history_button_p_    = new lon::Button(this);

	add_target_button_p_->setFixedSize(button_width_height,
                                       button_width_height);
    history_button_p_->setFixedSize(button_width_height, button_width_height);

    target_button_layout_p_->addWidget(add_target_button_p_);
    target_button_layout_p_->addWidget(history_button_p_);
    target_button_layout_p_->addSpacerItem(target_button_spacer_p_);

	target_main_layout_p_->addWidget(targets_list_widget_p_);
    target_main_layout_p_->addLayout(target_button_layout_p_);

	// set this widget..
    main_layout_p_->addLayout(labels_widget_main_layout_p_);
    main_layout_p_->addLayout(target_main_layout_p_);
    this->setLayout(main_layout_p_);

	// init label buttons..
    std::vector<QString> labels(sql_.getAllLabels());
    for (auto i : labels) {
        lon::Button *button_p = new lon::Button(labels_widget_p_);
        QWidget *    widget = new QWidget();
		//button_map_.emplace(std::make_pair(button_p, lon::AutoDeleteWidgetPointer(duration, widget)));
    }
}

void lon::LabelsAndTargetsWidget::onLabelButtonClicked() {
	lon::Button *button = qobject_cast<lon::Button*> (sender());
	//if(button_map_[button].isNull()) {
	//	QWidget *widget = new QWidget();
	//	auto iter = button_map_.find(button);
	//	button_map_.erase(iter);
 //       //button_map_.emplace(std::make_pair(
 //           //button, lon::AutoDeleteWidgetPointer(duration, widget)));
	//}
	// repalce current target list widget with targets belong the clicked label.
}

