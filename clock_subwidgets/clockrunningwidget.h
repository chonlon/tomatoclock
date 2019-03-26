#ifndef CLOCKRUNNINGWIDGET_H
#define CLOCKRUNNINGWIDGET_H

#include <QHBoxLayout>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>

#include "clockdisplaywidget.h"
#include "lon_widget/button.hpp"

namespace lon {
/// <summary>
/// 显示时钟的控件.
/// 用于嵌入到ClockMainWidget中.
/// </summary>
class ClockRunningWidget : public QWidget {
    Q_OBJECT
    // private:
  public:
    QHBoxLayout *main_layout_p_;
    QVBoxLayout *center_layout_p_;
    QHBoxLayout *bottom_button_layout_p_;
    QVBoxLayout *left_button_layout_p_;

    lon::Button *volume_button_p_;
    lon::Button *pause_button_p_;
    lon::Button *stop_button_p_;
    lon::Button *history_button_p_;
    lon::Button *setting_button_p_;

    lon::ClockDisplayWidget *clock_display_widget_p_;

    QSpacerItem *left_spacer_p_;
    QSpacerItem *right_spacer_p_;

    // center_layout到两边的边距
    const int8_t side_width;

  public:
    explicit ClockRunningWidget(QWidget *parent = nullptr);
    ~ClockRunningWidget();

  signals:

  public slots:
};
} // namespace lon

#endif // CLOCKRUNNINGWIDGET_H
