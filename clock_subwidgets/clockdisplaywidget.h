#ifndef CLOCKDISPLAYWIDGET_H
#define CLOCKDISPLAYWIDGET_H

#include <QWidget>
#include <QPainter>

#include "displayclockbase.h"


namespace lon {
class ClockDisplayWidget : public DisplayClockBase
{
    Q_OBJECT
private:
    double current_persent_;
    lon::ClockTime const *total_time_;
    std::unique_ptr<QString> left_time_string_p_;
    const lon::TimerStatus  *timer_status_;
    QBrush *current_brush_;
public:
    explicit ClockDisplayWidget(QWidget *parent = nullptr);

    virtual void updateTimeDisplay(lon::TimerStatus const *timer_status);
    virtual void paintEvent(QPaintEvent*);
signals:

public slots:
};

}
#endif // CLOCKDISPLAYWIDGET_H
