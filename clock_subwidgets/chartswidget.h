﻿#ifndef CHARTSWIDGET_H
#define CHARTSWIDGET_H

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>

#include "clock_database/clocksql.hpp"
#include "lon_widget/button.hpp"
#include "lon_widget/listwidget.hpp"


namespace lon {
class ChartsWidget : public QWidget {
    Q_OBJECT
  private:
    QComboBox *finish_line_combobox_p_;
    QComboBox *finishedtime_line_combobox_p_;
    QComboBox *label_pie_combobox_p_;
    QComboBox *target_pie_combobox_p_;

    QLabel *finish_line_label_p_;
    QLabel *finishedtime_line_label_p_;
    QLabel *label_pie_label_p_;
    QLabel *target_pie_label_p_;

    QWidget *finish_line_widget_p_;
    QWidget *finishedtime_line_widget_p_;
    QWidget *label_pie_widget_p_;
    QWidget *target_pie_widget_p_;

    QGridLayout *finish_line_layout_p_;
    QGridLayout *finishedtime_line_layout_p_;
    QGridLayout *label_pie_layout_p_;
    QGridLayout *target_pie_layout_p_;

    lon::ClockSql *sql_;

    lon::tomato_clock::TodayData     todaydata_;
    lon::tomato_clock::LastWeekData  lastweekdata_;
    lon::tomato_clock::LastMonthData lastmonthdata_;
    lon::tomato_clock::LastYearData  lastyeardata_;

    lon::ListWidget *list_widget_p_;
    lon::Button *    close_button_p_;

    QVBoxLayout *layout_p_;

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

    // init charts
    void initFinishedLineChart();
    void initFinishedTimeLineChart();
    void initLabelsPieChart();
    void initTargetsPieChart();
    void initBestworkTimeChart();

    // init widgets.
    void initFinishLinewidget();
    void initFinishedTimeLinewidget();
    void initLabelsPieWidget();
    void initTargetsPieWidget();
    void initBestworkTimeWidget();

  public:
    explicit ChartsWidget(lon::ClockSql *sql, QWidget *parent = nullptr);

    ~ChartsWidget();

  signals:
    void closeButtonClicked();
  public slots:
};
} // namespace lon

#endif // CHARTSWIDGET_H
