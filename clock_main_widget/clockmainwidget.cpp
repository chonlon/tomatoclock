#include "clockmainwidget.h"

#include "tomatoclocktimer.h"
#include "clock_subwidgets/chartswidget.h"
#include "clock_subwidgets/labelsandtargetswidget.h"
#include "clock_subwidgets/clockrunningwidget.h"
#include "clock_small_window/clocksmallwindow.h"
#include "lon_widget/messagebox.hpp"
#include "clock_database/clocksql.hpp"
using namespace lon;
//PRIVATE
void lon::ClockMainWidget::tomatoSaveToSql(QString label /*= QString("")*/, QString target /*= QString("")*/)
{
	auto duringtime = timer->timerStaus()->clock_options()->work_time()->minutes_;
	//if enabel break the tomato..
	//duringtime -= timer->timerStaus()->timeleft()->minutes();
	sql_p_->addAFinishedTomato(duringtime, "7", "��ѧ");
}


lon::ClockMainWidget::ClockMainWidget(QWidget *parent)
    : QWidget(parent), keep_working_(false) {
	sql_p_ = new lon::ClockSql();

	labels_targets_widget_p_ = new lon::LabelsAndTargetsWidget(sql_p_,this);
	clock_running_widget_p_ = nullptr;
	clock_small_window_p_ = nullptr;
	chart_widget_p_ = nullptr;

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

void lon::ClockMainWidget::displayTarget()
{
	// �л�����ʱ, ���������Ƶ��, �ʲ�����ԭ����.
	if (clock_running_widget_p_) {
		main_layout_->removeWidget(clock_running_widget_p_);
		delete clock_running_widget_p_;
		clock_running_widget_p_ = nullptr;
	} else if (chart_widget_p_) {
		main_layout_->removeWidget(chart_widget_p_);
		delete chart_widget_p_;
		chart_widget_p_ = nullptr;
	}

	labels_targets_widget_p_ = new lon::LabelsAndTargetsWidget(sql_p_, this);
	main_layout_->addWidget(labels_targets_widget_p_);
	connect(labels_targets_widget_p_, SIGNAL(startClock(const QString&, const QString&)), this, SLOT(displayClock(const QString&, const QString&)));
}

void lon::ClockMainWidget::displayChart()
{
	if (labels_targets_widget_p_) {
		main_layout_->removeWidget(labels_targets_widget_p_);
		delete labels_targets_widget_p_;
		labels_targets_widget_p_ = nullptr;
	}
	chart_widget_p_ = new lon::ChartsWidget(this);
	main_layout_->addWidget(chart_widget_p_);

}

void lon::ClockMainWidget::clockFinished()
{
	tomatoSaveToSql();
	if(keep_working_) {}
	else {
		lon::MessageBox *m = new lon::MessageBox(QString::fromLocal8Bit("�������"), QString::fromLocal8Bit("���������."));
		displayTarget();
	}
}

