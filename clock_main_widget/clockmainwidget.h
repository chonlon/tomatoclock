#ifndef CLOCKMAINWIDGET_H
#define CLOCKMAINWIDGET_H

#include <QGridLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QDateTime>

namespace lon {
	class LabelsAndTargetsWidget;
	class ClockRunningWidget;
	class TomatoClockTimer;
	class ClockSql;
	class ChartsWidget;
	namespace clock_window {
		class ClockSmallWindow;
	}
}
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
	  lon::ChartsWidget *chart_widget_p_;
	  lon::clock_window::ClockSmallWindow *clock_small_window_p_;


	  lon::TomatoClockTimer *timer;

	  QVBoxLayout *main_layout_;

	  lon::ClockSql *sql_p_;
private:
	void tomatoSaveToSql(QString label = QString(""), QString target = QString(""));
  public:
    explicit ClockMainWidget(QWidget *parent = nullptr);

  signals:

  public slots:
    // 是否切换显示计时
	void displayClock(const QString& label, const QString& target);
	void displayTarget();
	void displayChart();

	void clockFinished();
};
} // namespace lon

#endif // CLOCKMAINWIDGET_H
