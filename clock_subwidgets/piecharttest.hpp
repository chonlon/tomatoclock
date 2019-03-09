#ifndef PIECHARTTEST_H
#define PIECHARTTEST_H
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QHBoxLayout>
#include <QWidget>

class PieChartTest : public QWidget {
    Q_OBJECT
public:
    PieChartTest(QWidget *parent = nullptr) : QWidget(parent){

    }
};



#endif // PIECHARTTEST_H
