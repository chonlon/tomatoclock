#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "lon_widget/button.hpp"
#include "temp.h"
#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QGraphicsView>
#include <QLabel>
#include <QLayout>
#include <QPainter>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private:
    QLabel *        label;
    QHBoxLayout *   layout_;
    temp *          temp_;
    QGraphicsScene *scene;
    QPainter *      painter;
};

#endif // MAINWINDOW_H
