#include "clock_main_widget/clockmainwidget.h"
#include "clock_small_window/clocksmallwindow.h"
#include "clock_small_window/toolswidget.h"
#include "clock_subwidgets/addlabelwidget.h"
#include "clock_subwidgets/addtargetwidget.h"
#include "clock_subwidgets/chartswidget.h"
#include "clock_subwidgets/clockdisplaywidget.h"
#include "clock_subwidgets/clockrunningwidget.h"
#include "clock_subwidgets/labelsandtargetswidget.h"
#include "clock_subwidgets/piecharttest.hpp"
#include "clock_subwidgets/targetwidget.h"
#include "lon_widget/listwidget.hpp"
#include "lon_widget/messagebox.hpp"
#include "mainwindow.h"
#include "settingfileoperations.h"
#include "settingwidget.h"
#include "tomatoclocktimer.h"
#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //   lon::TomatoClockTimer *              timer = new
    //   lon::TomatoClockTimer();
    // lon::clock_window::ClockSmallWindow *s = new
    // lon::clock_window::ClockSmallWindow();
    // timer->setDisplayClockPointer(s->progress_widget_);
    // timer->start();
    // s->show();
    // lon::ClockRunningWidget *c = new lon::ClockRunningWidget();
    // lon::ClockDisplayWidget *w = new lon::ClockDisplayWidget();

    ////timer->setDisplayClockPointer(c->clock_display_widget_p_);
    // timer->setDisplayClockPointer(window->progress_widget_);

    // c->show();

    //    lon::ChartsWidget chartw;
    //    chartw.show();
    // lon::ClockMainWidget m;
    // m.show();
    // lon::TargetWidget t;
    // t.show();
    lon::ClockMainWidget *c = new lon::ClockMainWidget();
    c->show();
    return a.exec();
}