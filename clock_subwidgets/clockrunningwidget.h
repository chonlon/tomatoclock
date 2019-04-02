#ifndef CLOCKRUNNINGWIDGET_H
#define CLOCKRUNNINGWIDGET_H

#include "clock_small_window/clocksmallwindow.h"
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
/// <summary>
/// 显示时钟的控件.
/// 用于嵌入到ClockMainWidget中.
/// </summary>
class ClockRunningWidget : public QWidget {
    Q_OBJECT
  private:
    QGridLayout *                        main_layout_p_;
    QLabel *                             label_label_p_;
    QLabel *                             target_label_p_;
    lon::Button *                        stop_button_p_;
    lon::Button *                        small_window_switch_button_p_;
    lon::TomatoClockTimer *              timer_p_;
    lon::clock_window::ClockSmallWindow *small_window_p_;
    lon::ClockDisplayWidget *            main_display_widget_p_;
    lon::DisplayClockBase *              current_display_widget_p_;

  private:
    void setDisplayWidget(lon::DisplayClockBase *displaye_p);

  public:
    void setTimer(lon::TomatoClockTimer *timer);

  public:
    explicit ClockRunningWidget(const QString label_name,
                                const QString target_name,
                                QWidget *     parent = nullptr);
    ~ClockRunningWidget();

  signals:
    void clockStoped();
  public slots:
    void onStopButtonClicked();
    void onSmallWindowButtonClicked();

    // back to current widget from small widget.
    void backToCurrentWidget();
};
} // namespace lon

#endif // CLOCKRUNNINGWIDGET_H
