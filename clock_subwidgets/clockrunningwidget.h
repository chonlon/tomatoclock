#ifndef CLOCKRUNNINGWIDGET_H
#define CLOCKRUNNINGWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

#include "lon_widget/button.hpp"
#include "clockdisplaywidget.h"
namespace lon {

class ClockRunningWidget : public QWidget
{
    Q_OBJECT
//private:
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

    //center_layout到两边的边距
    const int8_t side_width;
public:
    explicit ClockRunningWidget(QWidget *parent = nullptr);
    ~ClockRunningWidget();

signals:

public slots:
};

}

#endif // CLOCKRUNNINGWIDGET_H
