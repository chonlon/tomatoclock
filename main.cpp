#include "clock_subwidgets/chartswidget.h"
#include "clock_small_window/clocksmallwindow.h"
#include "clock_small_window/toolswidget.h"
#include "clock_subwidgets/clockdisplaywidget.h"
#include "clock_subwidgets/clockrunningwidget.h"
#include "clock_subwidgets/piecharttest.hpp"
#include "lon_widget/listwidget.hpp"
#include "lon_widget/messagebox.hpp"
#include "mainwindow.h"
#include "tomatoclocktimer.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication                         a(argc, argv);
    //lon::TomatoClockTimer *              timer = new lon::TomatoClockTimer();
    //lon::clock_window::ClockSmallWindow *window =
    //    new lon::clock_window::ClockSmallWindow();
    //lon::ClockRunningWidget *c = new lon::ClockRunningWidget();
    //lon::ClockDisplayWidget *w = new lon::ClockDisplayWidget();

    //timer->setDisplayClockPointer(c->clock_display_widget_p_);
    //window->show();

    //c->show();

	lon::ChartsWidget chartw;
    chartw.show();
    return a.exec();
}
