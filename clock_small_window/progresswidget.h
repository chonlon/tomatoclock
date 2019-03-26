#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H

#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

#include "LonTypeDefines.h"
#include "displayclockbase.h"

namespace lon {
namespace clock_window {
class ProgressWidget : public DisplayClockBase {
    Q_OBJECT
  private:
    QGraphicsItem *current_progress_;

    QGraphicsScene *scene_;
    QGraphicsView * view_;

    QLabel *time_label_;

    QPen *pen_;

    lon::ClockTime const *total_time_;

    QHBoxLayout *layout_;
    QHBoxLayout *view_layout_;

    uint16_t height_;
    uint16_t width_;

  public:
    explicit ProgressWidget(QWidget *parent = nullptr);

    explicit ProgressWidget(uint16_t height, uint16_t width,
                            QWidget *parent = nullptr);

	~ProgressWidget();

    virtual void updateTimeDisplay(lon::TimerStatus const *timer_status);
  signals:

  public slots:
    /// <summary> 如果当前进度变化, 更新控件 </summary>
    /// <param name: current> 当前进度 </param>
    /// <param name: total> 所有的进度, current/total即为当前进度条的百分比
    /// </param>
    void progressChanged(uint16_t current, uint16_t total) {}
};
} // namespace clock_window
} // namespace lon

#endif // PROGRESSWIDGET_H
