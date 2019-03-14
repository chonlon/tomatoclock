#-------------------------------------------------
#
# Project created by QtCreator 2019-02-18T11:23:56
#
#-------------------------------------------------

QT       += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TomatoClock
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tomatoclocktimer.cpp \
    temp.cpp \
    main.cpp \
    mainwindow.cpp \
    temp.cpp \
    tomatoclocktimer.cpp \
    clock_small_window/clocksmallwindow.cpp \
    clock_small_window/progresswidget.cpp \
    clock_small_window/toolswidget.cpp \
    clock_main_widget/clockmainwidget.cpp \
    clock_main_widget/clockmainwidget.cpp \
    clock_subwidgets/clockdisplaywidget.cpp \
    clock_subwidgets/clockrunningwidget.cpp \
    clock_subwidgets/chartswidget.cpp \
    clock_subwidgets/labelsandtargetswidget.cpp \
    clock_subwidgets/targetwidget.cpp \
    clock_subwidgets/addlabelwidget.cpp \
    clock_subwidgets/addtargetwidget.cpp

HEADERS += \
        mainwindow.h \
    clockoptions.hpp \
    tomatoclocktimer.h \
    temp.h \
    clockoptions.hpp \
    mainwindow.h \
    temp.h \
    tomatoclocktimer.h \
    clock_small_window/clocksmallwindow.h \
    clock_small_window/progresswidget.h \
    clock_small_window/toolswidget.h \
    TimeStatus.hpp \
    LonTypeDefines.h \
    clock_main_widget/clockmainwidget.h \
    clock_main_widget/clockmainwidget.h \
    clock_subwidgets/clockdisplaywidget.h \
    displayclockbase.h \
    clock_subwidgets/clockrunningwidget.h \
    clock_database/finishedtomatosql.hpp \
    clock_database/clocksql.hpp \
    clock_database/DataStructure.hpp \
    clock_subwidgets/piecharttest.hpp \
    clock_subwidgets/chartswidget.h \
    clock_subwidgets/labelsandtargetswidget.h \
    clock_subwidgets/targetwidget.h \
    clock_subwidgets/addlabelwidget.h \
    clock_subwidgets/addtargetwidget.h \
    qstringhash.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Sub projects.
include(./lon_widget/lon_widget.pri)

FORMS += \
    temp.ui

RESOURCES += \
    img.qrc
