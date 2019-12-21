#ifndef CLOCKRUNNINGWIDGET_H
#define CLOCKRUNNINGWIDGET_H

#include "../clock_small_window/clocksmallwindow.h"
#include "clockdisplaywidget.h"

class QLabel;
class QGridLayout;
class QComboBox;

namespace lon {
class TomatoClockTimer;
class Button;

namespace clock_window {
class ClockSmallWindow;
}

/*!
 * \class ClockRunningWidget
 *
 * \brief 显示时钟的widget, 包含一个显示计时组件, 以及一些控制按钮.
 *
 * \author LON
 */
class ClockRunningWidget : public QWidget {
Q_OBJECT
private:
    QGridLayout* main_layout_p_;
    QLabel* label_label_p_;
    QLabel* target_label_p_;
    Button* stop_button_p_;
    Button* small_window_switch_button_p_;
    TomatoClockTimer* timer_p_;
    clock_window::ClockSmallWindow* small_window_p_;
    ClockDisplayWidget* main_display_widget_p_;
    DisplayClockBase* current_display_widget_p_;

private:

    /// <summary>
    /// 设置此类中接管计时器的DisplayClockBase.
    /// </summary>
    /// <param name="displaye_p">接管计时器者.</param>
    void setReceiveTimerWidget(DisplayClockBase* displaye_p);

protected:

public:

    /// <summary>
    /// 设置番茄钟计时器.
    /// </summary>
    /// <param name="timer">计时器指针.</param>
    void setTimer(TomatoClockTimer* timer);

    explicit ClockRunningWidget(QString label_name,
                                QString target_name,
                                QWidget* parent = nullptr);
    ~ClockRunningWidget();

signals:

    /// <summary>
    /// 提前中断番茄钟.
    /// </summary>
    void clockStoped();
public slots:

    /// <summary>
    /// 按下了stopbutton, 将会提前中断计时.
    /// </summary>
    void onStopButtonClicked();

    /// <summary>
    /// 按下了小窗口显示按钮, 将会切换小窗显示.
    /// </summary>
    void onSmallWindowButtonClicked();

    /// <summary>
    /// 从小窗显示返回主界面.
    /// </summary>
    void backToCurrentWidget();
};
} // namespace lon

#endif // CLOCKRUNNINGWIDGET_H
