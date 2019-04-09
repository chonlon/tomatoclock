#ifndef CLOCKDISPLAYWIDGET_H
#define CLOCKDISPLAYWIDGET_H

#include <QPainter>
#include <QWidget>

#include "displayclockbase.h"

namespace lon {
/*!
 * \class ClockDisplayWidget
 *
 * \brief ��ʾ��ʱ���, �������ʣ��ʱ�仭һ��Բ�ν�����
 *
 * \author LON
 */
class ClockDisplayWidget : public DisplayClockBase {
    Q_OBJECT
  private:
    double                   current_persent_;
    lon::ClockTime const *   total_time_;
    std::unique_ptr<QString> left_time_string_p_;
    const lon::TimerStatus * timer_status_;
    QBrush *                 current_brush_;

  public:
    explicit ClockDisplayWidget(QWidget *parent = nullptr);

	/// <summary>
	/// ����timer_status���¼�ʱ�Լ�������.
	/// </summary>
    virtual void updateTimeDisplay(lon::TimerStatus const *timer_status);
	/// <summary>
	/// �ڴ˽����ϻ�һ����������ʣ��ʱ��.
	/// </summary>
    virtual void paintEvent(QPaintEvent *);
  signals:

  public slots:
};
} // namespace lon
#endif // CLOCKDISPLAYWIDGET_H
