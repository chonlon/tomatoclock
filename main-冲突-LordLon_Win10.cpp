#include "clock_small_window/clocksmallwindow.h"
#include "clock_small_window/toolswidget.h"
#include "clock_subwidgets/clockdisplaywidget.h"
#include "clock_subwidgets/clockrunningwidget.h"
#include "clock_database/clocksql.hpp"
#include "lon_widget/listwidget.hpp"
#include "lon_widget/messagebox.hpp"
#include "mainwindow.h"
#include "tomatoclocktimer.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication                         a(argc, argv);
    lon::TomatoClockTimer *              timer = new lon::TomatoClockTimer();
    lon::clock_window::ClockSmallWindow *window =
        new lon::clock_window::ClockSmallWindow();
    lon::ClockRunningWidget *c = new lon::ClockRunningWidget();
    lon::ClockDisplayWidget *w = new lon::ClockDisplayWidget();
    timer->setDisplayClockPointer(c->clock_display_widget_p_);
    window->show();
    w->show();
    c->show();
    lon::ClockSql s;
    return a.exec();
}
