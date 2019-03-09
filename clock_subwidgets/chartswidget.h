﻿#ifndef CHARTSWIDGET_H
#define CHARTSWIDGET_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>

#include "clock_database/clocksql.hpp"
#include "lon_widget/listwidget.hpp"

namespace lon {
class ChartsWidget : public QWidget {
    Q_OBJECT
  private:
    lon::ClockSql sql_;

    lon::tomato_clock::TodayData     todaydata_;
    lon::tomato_clock::LastWeekData  lastweekdata_;
    lon::tomato_clock::LastMonthData lastmonthdata_;
    lon::tomato_clock::LastYearData  lastyeardata_;

    lon::ListWidget *list_widget_p_;

    QHBoxLayout *layout_p_;

    QtCharts::QChartView *finish_line_chart_view_p_;
    QtCharts::QChartView *finishedtime_line_chart_view_p_;
    QtCharts::QChartView *day_labels_pie_chart_view_p_;
    QtCharts::QChartView *week_labels_pie_chart_view_p_;
    QtCharts::QChartView *month_labels_pie_chart_view_p_;
    QtCharts::QChartView *day_targets_pie_chart_view_p_;
    QtCharts::QChartView *week_targets_pie_chart_view_p_;
    QtCharts::QChartView *month_targets_pie_chart_view_p_;
    QtCharts::QChartView *bestworktime_chart_view_p_;

    QtCharts::QChart *finished_day_line_chart_p_;
    QtCharts::QChart *finished_week_line_chart_p_;
    QtCharts::QChart *finished_month_line_chart_p_;

    QtCharts::QChart *finishedtime_week_line_chart_p_;
    QtCharts::QChart *finishedtime_month_line_chart_p_;
    QtCharts::QChart *finishedtime_year_line_chart_p_;

    QtCharts::QChart *day_labels_piechart_chart_p_;
    QtCharts::QChart *week_labels_piechart_chart_p_;
    QtCharts::QChart *month_labels_piechart_chart_p_;

    QtCharts::QChart *day_targets_piechart_chart_p_;
    QtCharts::QChart *week_targets_piechart_chart_p_;
    QtCharts::QChart *month_targets_piechart_chart_p_;

    /// <summary>
    /// 以data_array初始化一个包含QLineSeries的Chart.
    /// </summary>
    /// <param name="data_array">生成的series所用的数据.</param>
    /// <param name="length">data_array的长度.</param>
    /// <param name="title">生成series的标题.</param>
    /// <returns>生成的chart的指针.</returns>
    QtCharts::QChart *initLineChartSeries(uint16_t *   data_array,
                                          unsigned int length,
                                          QString      title = QString());
    /// <summary>
    /// 以labels_data初始化一个包含QPieSeries的Chart.
    /// </summary>
    /// <param name="labels_data">生成series所用的数据.</param>
    /// <param name="title">series的标题.</param>
    /// <returns>生成的chart的指针.</returns>
    QtCharts::QChart *
        initPieChartSeries(std::vector<std::pair<QString, int>> labels_data,
                           QString title = QString());
  public:
    explicit ChartsWidget(QWidget *parent = nullptr);

    ~ChartsWidget();

    void initFinishedLineChart();
    void initFinishedTimeLineChart();

    void initLabelsPieChart();

    void initTargetsPieChart();

    void initBestworkTimeChart();

  signals:

  public slots:
};
} // namespace lon

#endif // CHARTSWIDGET_H
