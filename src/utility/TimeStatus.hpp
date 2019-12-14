#ifndef TIMESTATUS_H
#define TIMESTATUS_H

#include <QDebug>
#include <exception>
#include <memory>

#include "clockoptions.hpp"

namespace lon {
class TimeLeft : public ClockTime {
public:
    TimeLeft()
        : ClockTime(0, 0) {
    }

    TimeLeft(int8_t minutes, int8_t seconds)
        : ClockTime(minutes, seconds) {
    }

    void clear() {
        minutes_ = 0;
        seconds_ = 0;
    }

    /// <summary>
    /// 剩余时间减一秒
    /// </summary>
    /// <returns>
    /// return 1 if success
    /// return 0 if left time just ran out
    /// return -1 if meet erro
    ///</returns>
    int8_t subOneSecond() {
        if (seconds_ == 0) {
            if (minutes_ == 0)
                return -1;
            --minutes_;
            seconds_ = 59;
            return 1;
        }
        if (--seconds_ == 0) {
            if (minutes_ == 0)
                return 0;
        }
        return 1;
    }

    int8_t minutes() const { return minutes_; }
    int8_t seconds() const { return seconds_; }

    void setMinutes(int8_t minutes) { minutes_ = minutes; }
    void setSeconds(int8_t seconds) { seconds_ = seconds; }
};

/// <summary> 目前计时器的状态, 包括剩余时间、和目前所在的番茄工作法的进度
/// </summary>
class TimerStatus {
private:
    // (is_break_ == true && short_break_times_ ==
    // clock_options_->sb_between_lb_) means long break
    typedef ClockTime CurrentTotalTime;
    bool is_break_;
    int8_t short_break_times_;
    TimeLeft* timeleft_;
    CurrentTotalTime const* total_time_;

    std::unique_ptr<ClockOptions> clock_options_;

private:
    enum NextStatus : int8_t { s_Working, s_ShortBreaking, s_LongBreaking };

    /// <summary> 获取现在的时钟信息, 具体处于什么状态. </summary>
    /// <returns>
    /// lon::CurrentStatus::s_Working 表示正在工作
    /// lon::CurrentStatus::s_ShortBreaking 表示正在短休息
    /// lon::CurrentStatus::s_LongBreaking 表示正在长休息
    /// </returns>
    NextStatus getNextStatus() const {
        if (is_break_)
            return s_Working;
        if (short_break_times_ < clock_options_->sbtimes_between_lb()) {
            return s_ShortBreaking;
        }
        return s_LongBreaking;
    }

public:
    /// <summary> TimerStatus的默认构造函数, 但是会导致TimeLeft未定义 </summary>
    TimerStatus()
        : is_break_(false),
          short_break_times_(0),
          timeleft_(new TimeLeft()) {
        qWarning() << "empty constructor in timerstatus";
    }

    /// <summary> 根据clock_options来设置剩余时间 </summary>
    TimerStatus(std::unique_ptr<ClockOptions>& clock_options)
        : is_break_(false),
          short_break_times_(0) {
        timeleft_ = new TimeLeft();
        clock_options_ = std::move(clock_options);
        total_time_ = clock_options_->work_time();
        timeleft_->setMinutes(clock_options_->work_time()->minutes_);
        timeleft_->setSeconds(clock_options_->work_time()->seconds_);
    }

    ~TimerStatus() { delete timeleft_; }

    /// <summary>
    /// 从剩余时间里面减去一秒.
    /// </summary>
    /// <returns> 下一段时间是否应为工作状态. </returns>
    bool subOneSecond() {
        int8_t status = timeleft_->subOneSecond();
        // 如果timeleft里面的时间不够, 设置下一段时间.
        if (status == 0) {
            int8_t next_status = getNextStatus();
            if (next_status == s_Working) {
                timeleft_->setMinutes(clock_options_->work_time()->minutes_);
                timeleft_->setSeconds(clock_options_->work_time()->seconds_);
                total_time_ = clock_options_->work_time();
                is_break_ = false;
                return true;
            }
            if (next_status == s_ShortBreaking) {
                timeleft_->setMinutes(clock_options_->sb_time()->minutes_);
                timeleft_->setSeconds(clock_options_->sb_time()->seconds_);
                is_break_ = true;
                total_time_ = clock_options_->sb_time();
                ++short_break_times_;
            } else {
                // s_LongBreaking
                timeleft_->setMinutes(clock_options_->lb_time()->minutes_);
                timeleft_->setSeconds(clock_options_->lb_time()->seconds_);
                is_break_ = true;
                total_time_ = clock_options_->lb_time();
                short_break_times_ = 0;
            }
        } else if (status == -1) {
            throw std::logic_error(
                "In timer_status, left time is less than zero");
        }

        return false;
    }

    void clear() { timeleft_->clear(); }

    TimeLeft const* timeleft() const { return timeleft_; }
    bool is_break() const { return is_break_; }
    int8_t short_break_times() const { return short_break_times_; }

    const std::unique_ptr<ClockOptions>& clock_options() const {
        return clock_options_;
    }

    CurrentTotalTime const* getTotalTime() const { return total_time_; }
};
} // namespace lon

#endif
