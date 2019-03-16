#ifndef CLOCKMAINWIDGET_H
#define CLOCKMAINWIDGET_H

#include <QGridLayout>
#include <QVBoxLayout>
#include <QWidget>

#include "tomatoclocktimer.h"
#include "clock_subwidgets/labelsandtargetswidget.h"
#include "clock_subwidgets/clockrunningwidget.h"
#include "clock_small_window/clocksmallwindow.h"
#include "lon_widget/messagebox.hpp"
namespace lon {
/// <summary>
/// 这个类是番茄钟在主界面显示的总widget.
/// </summary>
class ClockMainWidget : public QWidget {
    Q_OBJECT
  private:
	  bool keep_working_;

	  lon::LabelsAndTargetsWidget *labels_targets_widget_p_;
	  lon::ClockRunningWidget *clock_running_widget_p_;
	  lon::clock_window::ClockSmallWindow *clock_small_window_p_;

	  lon::TomatoClockTimer *timer;

	  QVBoxLayout *main_layout_;
private:
	void tomatoSaveToSql(QString time, QString label = QString(""), QString target = QString("")) {}
  public:
    explicit ClockMainWidget(QWidget *parent = nullptr);

  signals:

  public slots:
    // 是否切换显示计时
	void displayClock(const QString& label, const QString& target);
	void dispalyTarget();

	void clockFinished();
};
} // namespace lon

#endif // CLOCKMAINWIDGET_H
