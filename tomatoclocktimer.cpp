#include "tomatoclocktimer.h"
#include "settingfileoperations.h"
#include <QDebug>
#include <exception>

void lon::TomatoClockTimer::setDisplayClockPointer(
    DisplayClockBase *display_clock) {
    display_clock_ = display_clock;
}

lon::TomatoClockTimer::TomatoClockTimer(QObject *parent)
    : QObject(parent)
    , started_(false) {
    display_clock_ = nullptr;
    timer_         = new QTimer(this);
    timer_->start(1000);
    std::unique_ptr<lon::ClockOptions> clock(new lon::ClockOptions(
        SettingFileOperations().readClockOptionFromFile()));
    timer_status_ = new lon::TimerStatus(clock);
    connect(timer_, SIGNAL(timeout()), this, SLOT(oneSecondPassed()));
}

void lon::TomatoClockTimer::oneSecondPassed() {
    if (!started_) return;
    bool finish = timer_status_->subOneSecond();

    if (finish) {
        stop();
        emit tomatoFinished();
        return;
    }

    qDebug("%d : %d", timer_status_->timeleft()->minutes(),
           timer_status_->timeleft()->seconds());

    if (display_clock_) display_clock_->updateTimeDisplay(timer_status_);
}