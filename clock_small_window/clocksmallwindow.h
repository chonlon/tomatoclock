#ifndef CLOCKSMALLWINDOW_H
#define CLOCKSMALLWINDOW_H

#include <QBrush>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QWidget>

#include "LonTypeDefines.h"
#include "clock_small_window/progresswidget.h"
#include "clock_small_window/toolswidget.h"

namespace lon {
namespace clock_window {
/// <summary>
/// 小窗显示番茄钟的控件.
/// </summary>
class ClockSmallWindow : public QWidget {
    Q_OBJECT
  private:
    bool   is_pressed_;
    QPoint move_start_position_;

  protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

  public:
    QPixmap *window_background_;

    ProgressWidget *progress_widget_;

    QHBoxLayout *layout_;

  public:
    explicit ClockSmallWindow(QWidget *parent = nullptr);

	~ClockSmallWindow();

    const uint16_t fixed_height_;
    const uint16_t fixed_width_;
  signals:

  public slots:
};
} // namespace clock_window
} // namespace lon
#endif // CLOCKSMALLWINDOW_H
