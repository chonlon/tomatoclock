/***********************************************************************
TomatoClock
Developer: lon

Classes:
    ClockOptions : Clock's time options, which sets how long the clock and the
break is.
***********************************************************************/

#ifndef CLOCKOPTIONS_H
#define CLOCKOPTIONS_H
#include "LonTypeDefines.h"
#include <QTime>
#include <QTimer>

namespace lon {
/////////////////////////////
// clock times
/////////////////////////////
/// brief The ClockTime struct

/*!
 * \class ClockTime
 *
 * \brief 所有Timer的基类
 *
 * \author LON
 */
struct ClockTime {
    int8_t minutes_;
    int8_t seconds_;

    ClockTime(int8_t minutes, int8_t seconds) : minutes_(minutes), seconds_(seconds) {}
};

/*!
 * \class ClockOptions
 *
 * \brief 番茄钟的所有Options.
 *
 * \author LON
 */
class ClockOptions {
private:
    typedef ClockTime ShortBreakTime;
    typedef ClockTime LongBreakTime;
    typedef ClockTime WorkTime;

    WorkTime* work_time_;
    ShortBreakTime* sb_time_;
    LongBreakTime* lb_time_;
    int8_t sbtimes_between_lb_;
    bool keep_working_;

public:
    ClockOptions()
        : work_time_(new WorkTime(25, 0)),
          sb_time_(new ShortBreakTime(5, 0)),
          lb_time_(new LongBreakTime(15, 0)),
          sbtimes_between_lb_(3),
          keep_working_(false) {}

    /// <summary> 这个构造函数主要是在用户自定义时间参数以后,
    /// 为各个参数提供初始化 </summary>
    ClockOptions(int8_t clock_time_min,
                 int8_t clock_time_sec,
                 int8_t short_break_min,
                 int8_t short_break_sec,
                 int8_t long_break_min,
                 int8_t long_break_sec,
                 int8_t sbtimes_between_lb,
                 bool keep_working)
        : work_time_(new WorkTime(clock_time_min, clock_time_sec)),
          sb_time_(new ShortBreakTime(short_break_min, short_break_sec)),
          lb_time_(new LongBreakTime(long_break_min, long_break_sec)),
          sbtimes_between_lb_(sbtimes_between_lb),
          keep_working_(keep_working) {}

    ClockOptions(const ClockOptions& option) {
        work_time_ = new WorkTime(*(option.work_time()));
        sb_time_ = new ShortBreakTime(*(option.sb_time()));
        lb_time_ = new LongBreakTime(*(option.lb_time()));
        set_sbtimes_between_lb(option.sbtimes_between_lb());
        keep_working_ = option.keepWorking();
    }

    ClockOptions(ClockOptions&& clock_option) {
        work_time_ = const_cast<ClockTime*>(clock_option.work_time());
        sb_time_ = const_cast<ClockTime*>(clock_option.sb_time());
        lb_time_ = const_cast<ClockTime*>(clock_option.lb_time());
        set_sbtimes_between_lb(clock_option.sbtimes_between_lb());
        keep_working_ = clock_option.keepWorking();
    }

    ~ClockOptions() {
        delete work_time_;
        delete sb_time_;
        delete lb_time_;
    }

    bool setWorkTime(int8_t clock_time_min, int8_t clock_time_sec) {
        if (clock_time_sec > 60 || clock_time_min > 100)
            return false;
        work_time_->minutes_ = clock_time_min;
        work_time_->seconds_ = clock_time_sec;
        return true;
    }

    bool setShortBreakTime(int8_t short_break_min, int8_t short_break_sec) {
        if (short_break_sec > 60 || short_break_min > 100)
            return false;
        sb_time_->minutes_ = short_break_min;
        sb_time_->seconds_ = short_break_sec;
        return true;
    }

    bool setLongBreakTime(int8_t long_break_min, int8_t long_break_sec) {
        if (long_break_sec > 60 || long_break_min > 100)
            return false;
        lb_time_->minutes_ = long_break_min;
        lb_time_->seconds_ = long_break_sec;
        return true;
    }

    ClockTime const* work_time() const {
        return work_time_;
    }

    ShortBreakTime const* sb_time() const {
        return sb_time_;
    }

    LongBreakTime const* lb_time() const {
        return lb_time_;
    }

    int8_t sbtimes_between_lb() const {
        return sbtimes_between_lb_;
    }

    bool keepWorking() const {
        return keep_working_;
    }
    void setKeepWorking(bool val) {
        keep_working_ = val;
    }
    void set_sbtimes_between_lb(int8_t val) {
        sbtimes_between_lb_ = val;
    }
};
}  // namespace lon

#endif  // CLOCKOPTIONS_H
