﻿#ifndef CLOCKSMALLWINDOW_H
#define CLOCKSMALLWINDOW_H

#include <QBrush>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QWidget>

#include "LonTypeDefines.h"
#include "progresswidget.h"
#include "toolswidget.h"

namespace lon {
namespace clock_window {
/// <summary>
/// 小窗显示番茄钟的控件.
/// </summary>
class ClockSmallWindow : public QWidget {
    Q_OBJECT
private:
    bool is_pressed_;
    QPoint move_start_position_;
    QHBoxLayout* layout_;
    QPixmap* window_background_;
    ToolsWidget* tools_widget_;

protected:
    // 鼠标移入移除事件.
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

    // 三个函数实现窗口的拖动.
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    // 鼠标滚轮事件, 滚轮改变窗口透明度.
    void wheelEvent(QWheelEvent* event) override;

public:
    ProgressWidget* progress_widget_;

public:
    explicit ClockSmallWindow(const QString& label_name,
                              const QString& target_name,
                              QWidget* parent = nullptr);

    ~ClockSmallWindow();

    const uint16_t fixed_height_;
    const uint16_t fixed_width_;
signals:
    /// <summary>
    /// 提前终止番茄钟.
    /// </summary>
    void clockStoped();

    /// <summary>
    /// 小窗正在关闭.
    /// </summary>
    void smallWindowClosing();

public slots:
};
}  // namespace clock_window
}  // namespace lon
#endif  // CLOCKSMALLWINDOW_H
