#ifndef PIECHARTTEST_H
#define PIECHARTTEST_H
#include <QHBoxLayout>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QtCharts>



class PieChartTest : public QWidget {
    Q_OBJECT
  public:
    PieChartTest(QWidget *parent = nullptr)
        : QWidget(parent) {}
};

#endif // PIECHARTTEST_H