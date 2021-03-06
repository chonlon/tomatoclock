﻿#ifndef CHARTSWIDGET_H
#define CHARTSWIDGET_H

#include "clock_database/clocksql.hpp"
#include <QWidget>
#include <memory>

class QComboBox;
class QLabel;
class QGridLayout;
class QVBoxLayout;

namespace lon {
class ListWidget;
class Button;
}  // namespace lon
namespace QtCharts {
class QChartView;
class QChart;
}  // namespace QtCharts

namespace lon {
/*!
 * \class ChartsWidget
 *
 * \brief 显示图表类, 包括两个折线图, 两个饼图.
 *
 * \author LON
 */
class ChartsWidget : public QWidget {
    Q_OBJECT
private:
    QComboBox* finish_line_combobox_p_;
    QComboBox* finishedtime_line_combobox_p_;
    QComboBox* label_pie_combobox_p_;
    QComboBox* target_pie_combobox_p_;

    QLabel* finish_line_label_p_;
    QLabel* finishedtime_line_label_p_;
    QLabel* label_pie_label_p_;
    QLabel* target_pie_label_p_;

    QWidget* finish_line_widget_p_;
    QWidget* finishedtime_line_widget_p_;
    QWidget* label_pie_widget_p_;
    QWidget* target_pie_widget_p_;

    QGridLayout* finish_line_layout_p_;
    QGridLayout* finishedtime_line_layout_p_;
    QGridLayout* label_pie_layout_p_;
    QGridLayout* target_pie_layout_p_;

    ClockSql* sql_;

    std::shared_ptr<tomato_clock::TodayData> todaydata_p_;
    std::shared_ptr<tomato_clock::LastWeekData> lastweekdata_p_;
    std::shared_ptr<tomato_clock::LastMonthData> lastmonthdata_p_;
    std::shared_ptr<tomato_clock::LastYearData> lastyeardata_p_;

    // todo 在listwidget的右边显示一个指示栏。
    ListWidget* list_widget_p_;
    Button* close_button_p_;

    QVBoxLayout* layout_p_;

    QtCharts::QChartView* day_finish_line_chart_view_p_;
    QtCharts::QChartView* week_finish_line_chart_view_p_;
    QtCharts::QChartView* month_finish_line_chart_view_p_;
    QtCharts::QChartView* week_finishedtime_line_chart_view_p_;
    QtCharts::QChartView* month_finishedtime_line_chart_view_p_;
    QtCharts::QChartView* day_finishedtime_line_chart_view_p_;
    QtCharts::QChartView* day_labels_pie_chart_view_p_;
    QtCharts::QChartView* week_labels_pie_chart_view_p_;
    QtCharts::QChartView* month_labels_pie_chart_view_p_;
    QtCharts::QChartView* day_targets_pie_chart_view_p_;
    QtCharts::QChartView* week_targets_pie_chart_view_p_;
    QtCharts::QChartView* month_targets_pie_chart_view_p_;
    QtCharts::QChartView* bestworktime_chart_view_p_;

    QtCharts::QChart* finished_day_line_chart_p_;
    QtCharts::QChart* finished_week_line_chart_p_;
    QtCharts::QChart* finished_month_line_chart_p_;

    QtCharts::QChart* finishedtime_week_line_chart_p_;
    QtCharts::QChart* finishedtime_month_line_chart_p_;
    QtCharts::QChart* finishedtime_day_line_chart_p_;

    QtCharts::QChart* day_labels_piechart_chart_p_;
    QtCharts::QChart* week_labels_piechart_chart_p_;
    QtCharts::QChart* month_labels_piechart_chart_p_;

    QtCharts::QChart* day_targets_piechart_chart_p_;
    QtCharts::QChart* week_targets_piechart_chart_p_;
    QtCharts::QChart* month_targets_piechart_chart_p_;

    /// <summary>
    /// 以data_array初始化一个包含QLineSeries的Chart.
    /// </summary>
    /// <param name="data_array">生成的series所用的数据.</param>
    /// <param name="title">生成series的标题.</param>
    /// <returns>生成的chart的指针.</returns>
    template<size_t Size>
    QtCharts::QChart* initLineChartSeries(const std::array<uint16_t, Size>& data_array,
                                          QString title = QString());
    /// <summary>
    /// 以labels_data初始化一个包含QPieSeries的Chart.
    /// </summary>
    /// <param name="labels_data">生成series所用的数据.</param>
    /// <param name="title">series的标题.</param>
    /// <returns>生成的chart的指针.</returns>
    QtCharts::QChart* initPieChartSeries(std::vector<std::pair<QString, int>> labels_data,
                                         QString title = QString());

    // init charts
    void initDayFinishedLineChart();
    void initWeekFinishedLineChart();
    void initMonthFinishedLineChart();
    void initWeekFinishedTimeLineChart();
    void initMonthFinishedTimeLineChart();
    void initDayFinishedTimeLineChart();
    void initFinishedTimeLineChart();
    void initDayLabelsPieChart();
    void initWeekLabelsPieChart();
    void initMonthLabelsPieChart();
    void initDayTargetsPieChart();
    void initWeekTargetsPieChart();
    void initMonthTargetsPieChart();
    void initBestworkTimeChart();

    // init widgets.
    void initFinishLinewidget();
    void initFinishedTimeLinewidget();
    void initLabelsPieWidget();
    void initTargetsPieWidget();
    void initBestworkTimeWidget();

public:
    explicit ChartsWidget(std::shared_ptr<tomato_clock::TodayData> todaydata_p,
                          std::shared_ptr<tomato_clock::LastWeekData> lastweekdata_p,
                          std::shared_ptr<tomato_clock::LastMonthData> lastmonthdata_p,
                          QWidget* parent = nullptr);
    ~ChartsWidget();

signals:
    void closeButtonClicked();
public slots:
    // 每个图的时间段切换事件.
    void finishLineWidgetSwitchEvent(int index);
    void finishedTimeLineWidgetSwitchEvent(int index);
    void labelsPieWidgetSwitchEvent(int index);
    void targetsPieWidgetSwitchEvent(int index);
};
}  // namespace lon

#endif  // CHARTSWIDGET_H
