#ifndef CLOCKDISPLAYWIDGET_H
#define CLOCKDISPLAYWIDGET_H

#include <QPainter>
#include <QWidget>

#include "../displayclockbase.h"

namespace lon {
/*!
 * \class ClockDisplayWidget
 *
 * \brief 显示计时组件, 将会根据剩余时间画一个圆形进度条
 *
 * \author LON
 */
class ClockDisplayWidget : public DisplayClockBase {
Q_OBJECT
private:
    double current_persent_;
    ClockTime const* total_time_;
    std::unique_ptr<QString> left_time_string_p_;
    const TimerStatus* timer_status_;
    QBrush* current_brush_;

public:
    explicit ClockDisplayWidget(QWidget* parent = nullptr);

    /// <summary>
    /// 根据timer_status更新计时以及进度条.
    /// </summary>
    void updateTimeDisplay(TimerStatus const* timer_status) override;
    /// <summary>
    /// 在此界面上画一个进度条和剩余时间.
    /// </summary>
    void paintEvent(QPaintEvent*) override;
signals:

public slots:
};
} // namespace lon
#endif // CLOCKDISPLAYWIDGET_H
