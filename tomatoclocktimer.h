#ifndef TOMATOCLOCKTIMER_H
#define TOMATOCLOCKTIMER_H

#include <QDebug>
#include <QObject>
#include <QTimer>
#include <memory>

#include "TimeStatus.hpp"
#include "displayclockbase.h"

namespace lon {
/// <summary> ������ʱ�� </summary>
class TomatoClockTimer : public QObject {
    Q_OBJECT
  private:
	bool started_;

    TimerStatus *     timer_status_;
    QTimer *          timer_;
    DisplayClockBase *display_clock_;

	void stop() { started_ = false; }
  public:
    explicit TomatoClockTimer(QObject *parent = nullptr);

    void setDisplayClockPointer(DisplayClockBase *display_clock);

	void start() { started_ = true; }

	/// <summary>
	/// ����˴�����, ���緬������;���ر�, ���˵���һ��״̬, ��ֹͣ��ʱ.
	/// </summary>
	void clearRunning() {}
  signals:
	  void tomatoFinished();
  public slots:
  private slots:
    void oneSecondPassed();
};
} // namespace lon
#endif // TOMATOCLOCKTIMER_H
