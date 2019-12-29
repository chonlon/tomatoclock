﻿#ifndef TOMATOCLOCKTIMER_H
#define TOMATOCLOCKTIMER_H

#include <QDebug>
#include <QObject>
#include <QTimer>
#include <memory>

#include "TimeStatus.hpp"
#include "src/gui/displayclockbase.h"

namespace lon {
/// <summary> 工作法时钟 </summary>
class TomatoClockTimer : public QObject {
    Q_OBJECT
private:
    bool running_;

    TimerStatus* timer_status_;
    QTimer* timer_;
    DisplayClockBase* display_clock_;

public:
    explicit TomatoClockTimer(QObject* parent = nullptr);

    void setDisplayClockPointer(DisplayClockBase* display_clock);

    void clear() {
        timer_status_->clear();
    }

    void stop() {
        running_ = false;
    }

    void start() {
        running_ = true;
    }

    TimerStatus const* timerStaus() {
        return timer_status_;
    }

    /// <summary>
    /// 清除此次运行, 比如番茄钟中途被关闭, 回退到上一个状态, 并停止计时.
    /// </summary>
    void clearRunning() {}

signals:
    void tomatoFinished();
public slots:
private slots:
    void oneSecondPassed();
};
}  // namespace lon
#endif  // TOMATOCLOCKTIMER_H
