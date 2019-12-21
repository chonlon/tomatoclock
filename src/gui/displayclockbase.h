#ifndef DISPLAYCLOCKWIDGET_H
#define DISPLAYCLOCKWIDGET_H

#include <QBrush>
#include <QWidget>

#include <memory>

#include "TimeStatus.hpp"

namespace lon {
/// <summary>
/// 显示番茄钟的widget的基类, 主要提供timer的更新和time数据.
/// </summary>
class DisplayClockBase : public QWidget {
    Q_OBJECT
protected:
    QBrush* working_foreground_brush_;
    QBrush* shortbreaking_foreground_brush_;
    QBrush* longbreaking_foreground_brush_;

    /// <summary>
    /// 计算当前已经过时间所占总时间的百分比.
    /// </summary>
    /// <param name="timer_status"> 根据timer_status_计算百分比 </param>
    /// <returns> 百分比结果 </returns>
    double currentPersent(TimerStatus const* timer_status) {
        ClockTime const* total_time = timer_status->getTotalTime();
        int total = total_time->minutes_ * 60 + total_time->seconds_;
        if (total == 0)
            return -1;
        int left = timer_status->timeleft()->minutes() * 60 + timer_status->timeleft()->seconds();
        int current_passed_time = total - left;

        // qDebug() << "++" << current_passed_time << "--" << total;
        return static_cast<double>(current_passed_time) / total;
    }

    /// <summary>
    /// 计算剩余时间.
    /// </summary>
    /// <param name="timer_status"> 根据timer_status计算剩余时间. </param>
    /// <returns> 剩余时间的QString类型的指针, 内存的所有权会被移交给调用者.
    /// </returns>
    std::unique_ptr<QString> leftTimeString(TimerStatus const* timer_status) {
        std::unique_ptr<QString> result(new QString());
        result->append(QString::number(timer_status->timeleft()->minutes()));
        result->append(" : ");
        int8_t s = timer_status->timeleft()->seconds();
        if (s < 10)
            result->append('0');
        result->append(QString::number(timer_status->timeleft()->seconds()));

        return std::move(result);
        //这里还是应该使用move的, 但会有个warning,
        //而且编译器一般来说会自动加上move return result;
    }

public:
    explicit DisplayClockBase(QWidget* parent = nullptr) : QWidget(parent) {
        working_foreground_brush_ = new QBrush(QColor(255, 255, 255, 180));
        shortbreaking_foreground_brush_ = new QBrush(QColor(30, 239, 61, 180));
        longbreaking_foreground_brush_ = new QBrush(QColor(33, 252, 217, 180));
    }

    virtual ~DisplayClockBase() {
        delete working_foreground_brush_;
        delete shortbreaking_foreground_brush_;
        delete longbreaking_foreground_brush_;
    }

signals:

public slots:
    /// <summary> 更新界面时间相关控件. </summary>
    /// <param name = "timer_status">
    /// 根据此参数设置控件
    /// </param>
    virtual void updateTimeDisplay(TimerStatus const* timer_status) = 0;
};
}  // namespace lon

#endif  // DISPLAYCLOCKWIDGET_H
