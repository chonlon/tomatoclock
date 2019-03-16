#include "clockmainwidget.h"
using namespace lon;

lon::ClockMainWidget::ClockMainWidget(QWidget *parent)
    : QWidget(parent), keep_working_(false) {
	labels_targets_widget_p_ = new lon::LabelsAndTargetsWidget(this);
	clock_running_widget_p_ = nullptr;
	clock_small_window_p_ = nullptr;

	timer = nullptr;

	main_layout_ = new QVBoxLayout(this);
	main_layout_->addWidget(labels_targets_widget_p_);
	connect(labels_targets_widget_p_, SIGNAL(startClock(const QString&, const QString&)), this, SLOT(displayClock(const QString&, const QString&)));
	this->setLayout(main_layout_);
}

void lon::ClockMainWidget::displayClock(const QString& label, const QString& target)
{
	if (labels_targets_widget_p_) {
		main_layout_->removeWidget(labels_targets_widget_p_);
		delete labels_targets_widget_p_;
		labels_targets_widget_p_ = nullptr;
	}

	if (!timer) {
		timer = new lon::TomatoClockTimer(this);
		connect(timer, SIGNAL(tomatoFinished()), this, SLOT(clockFinished()));
	}
	timer->start();

	clock_running_widget_p_ = new lon::ClockRunningWidget(this);
	main_layout_->addWidget(clock_running_widget_p_);
	timer->setDisplayClockPointer(clock_running_widget_p_->clock_display_widget_p_);
}

void lon::ClockMainWidget::dispalyTarget()
{
	// 切换界面时, 操作不频繁, 故不保留原界面.
	if (clock_running_widget_p_) {
		main_layout_->removeWidget(clock_running_widget_p_);
		delete clock_running_widget_p_;
		clock_running_widget_p_ = nullptr;
	}

	labels_targets_widget_p_ = new lon::LabelsAndTargetsWidget(this);
	main_layout_->addWidget(labels_targets_widget_p_);
	connect(labels_targets_widget_p_, SIGNAL(startClock(const QString&, const QString&)), this, SLOT(displayClock(const QString&, const QString&)));
}

void lon::ClockMainWidget::clockFinished()
{
	if(keep_working_) {}
	else {
		lon::MessageBox m(QString::fromLocal8Bit("番茄完成"), QString::fromLocal8Bit("番茄已完成."));
		dispalyTarget();
	}
}

