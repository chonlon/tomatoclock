#include "tomatoclocktimer.h"
#include <QDebug>
#include <exception>

void lon::TomatoClockTimer::setDisplayClockPointer(
    DisplayClockBase *display_clock) {
    display_clock_ = display_clock;
}

lon::TomatoClockTimer::TomatoClockTimer(QObject *parent)
    : QObject(parent) {
    timer_ = new QTimer(this);
    timer_->start(10);
    std::unique_ptr<lon::ClockOptions> clock(new lon::ClockOptions());
    timer_status_ = new lon::TimerStatus(clock);
    connect(timer_, SIGNAL(timeout()), this, SLOT(oneSecondPassed()));
}

void lon::TomatoClockTimer::oneSecondPassed() {
    timer_status_->subOneSecond();
    qDebug("%d : %d", timer_status_->timeleft()->minutes(),
           timer_status_->timeleft()->seconds());

    display_clock_->updateTimeDisplay(timer_status_);
}
