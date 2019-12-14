// encoded with gbk, cause QString::fromUtf8 doesn't work.
#include "chartswidget.h"
#include "../lon_widget/button.hpp"
#include "../lon_widget/listwidget.hpp"

#include <algorithm>

#include <QMessageBox>
#include <QtCharts/QValueAxis>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>


/*
 *	#staic
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#pragma execution_character_set("utf-8")
#endif

static const int chart_view_height_ = 500;

/// <summary>
/// 通过给定的tickcount 和 最大值来确定坐标最大值以便使每个纵坐标恰好为整数.
/// </summary>
static inline int makeAxisInteger(const int& tick_count, const int& max) {
    if (!tick_count)
        return max;
    int _tick_count = tick_count - 1;
    int distence = max / _tick_count;
    return max % _tick_count
        ? distence * _tick_count + _tick_count
        : distence * _tick_count;
}

/*
 *	#member
 */

QtCharts::QChart* lon::ChartsWidget::initLineChartSeries(
    uint16_t* data_array,
    unsigned int length,
    QString title /*= QString()*/) {
    using namespace QtCharts;
    //所有的chart的所有权会被被转移到chartview中, 所以不用担心这里会内存泄漏.
    QChart* chart = new QChart();
    chart->setTitle(title);
    // chart will take series's ownship.
    QLineSeries* series = new QLineSeries(chart);
    series->setPointLabelsColor(QColor(251, 192, 45));
    series->setPointLabelsVisible(true);
    series->setPointLabelsFormat("@yPoint");
    series->setPointsVisible(true);
    for (int i = 0; i < length; ++i) {
        series->append(i, data_array[i]);
    }
    chart->addSeries(series);

    //设置chart的导航线(axes)
    int _max = *std::max_element(data_array, data_array + length);
    //避免纵轴长度为零
    _max = std::max(2, _max);

    chart->createDefaultAxes();
    auto ver_axis =
        dynamic_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    auto hor_axis =
        dynamic_cast<QValueAxis *>(chart->axes(Qt::Horizontal).first());
    ver_axis->setGridLineVisible(true);
    //当纵轴很长时只取最大15, 避免卡顿
    ver_axis->setTickCount(std::min(15, _max + 1) + 1);
    ver_axis->setRange(0, makeAxisInteger(ver_axis->tickCount(), _max));
    ver_axis->setLabelFormat("%d");
    hor_axis->setRange(0, std::max(length - 1, static_cast<unsigned int>(1)));
    hor_axis->setGridLineVisible(true);
    hor_axis->setTickCount(length);
    hor_axis->setLabelFormat("%d");
    chart->legend()->setVisible(false);
    return chart;
}

QtCharts::QChart* lon::ChartsWidget::initPieChartSeries(
    std::vector<std::pair<QString, int>> labels_data,
    QString title /*= QString()*/) {
    using namespace QtCharts;
    QChart* chart = new QChart();
    chart->setTitle(title);
    QPieSeries* series = new QPieSeries(chart);
    for (int i = 0; i < labels_data.size(); ++i) {
        QPieSlice* slice =
            series->append(labels_data[i].first, labels_data[i].second);
        slice->setLabel(
            QString("%1: %2").arg(slice->label()).arg(slice->value()));
        slice->setLabelVisible(true);
    }
    series->setPieSize(0.6);
    chart->addSeries(series);
    chart->legend()->setAlignment(Qt::AlignRight);
    // #add function fail
    // chart->setTheme(QChart::ChartTheme::ChartThemeBlueIcy);

    return chart;
}

void lon::ChartsWidget::initDayFinishedLineChart() {
    using namespace QtCharts;
    finished_day_line_chart_p_ =
        initLineChartSeries(todaydata_p_->time_data_p, todaydata_p_->length);
    day_finish_line_chart_view_p_ =
        new QChartView(finished_day_line_chart_p_, this);
    day_finish_line_chart_view_p_->setFixedHeight(chart_view_height_);
}

void lon::ChartsWidget::initWeekFinishedLineChart() {
    using namespace QtCharts;
    finished_week_line_chart_p_ = initLineChartSeries(
        lastweekdata_p_->time_data_p,
        lastweekdata_p_->length);
    week_finish_line_chart_view_p_ =
        new QChartView(finished_week_line_chart_p_, this);
    week_finish_line_chart_view_p_->setFixedHeight(chart_view_height_);
}

void lon::ChartsWidget::initMonthFinishedLineChart() {
    using namespace QtCharts;
    finished_month_line_chart_p_ = initLineChartSeries(
        lastmonthdata_p_->time_data_p,
        lastmonthdata_p_->length);
    month_finish_line_chart_view_p_ =
        new QChartView(finished_month_line_chart_p_, this);
    month_finish_line_chart_view_p_->setFixedHeight(chart_view_height_);
}

void lon::ChartsWidget::initDayFinishedTimeLineChart() {
    using namespace QtCharts;
    finishedtime_day_line_chart_p_ =
        initLineChartSeries(todaydata_p_->total_time_p, todaydata_p_->length);
    day_finishedtime_line_chart_view_p_ =
        new QChartView(finishedtime_day_line_chart_p_, this);
    day_finishedtime_line_chart_view_p_->setFixedHeight(chart_view_height_);
}

void lon::ChartsWidget::initWeekFinishedTimeLineChart() {
    using namespace QtCharts;
    finishedtime_week_line_chart_p_ = initLineChartSeries(
        lastweekdata_p_->total_time_p,
        lastweekdata_p_->length);
    week_finishedtime_line_chart_view_p_ =
        new QChartView(finishedtime_week_line_chart_p_, this);
    week_finishedtime_line_chart_view_p_->setFixedHeight(chart_view_height_);
}

void lon::ChartsWidget::initMonthFinishedTimeLineChart() {
    using namespace QtCharts;
    finishedtime_month_line_chart_p_ = initLineChartSeries(
        lastmonthdata_p_->total_time_p,
        lastmonthdata_p_->length);
    month_finishedtime_line_chart_view_p_ =
        new QChartView(finishedtime_month_line_chart_p_, this);
    month_finishedtime_line_chart_view_p_->setFixedHeight(chart_view_height_);
}

void lon::ChartsWidget::initFinishedTimeLineChart() {
    using namespace QtCharts;
    finishedtime_week_line_chart_p_ = initLineChartSeries(
        lastweekdata_p_->total_time_p,
        lastweekdata_p_->length);
    week_finishedtime_line_chart_view_p_ =
        new QChartView(finishedtime_week_line_chart_p_, this);
}

void lon::ChartsWidget::initDayLabelsPieChart() {
    using namespace QtCharts;
    day_labels_piechart_chart_p_ = initPieChartSeries(todaydata_p_->label_data);

    day_labels_pie_chart_view_p_ =
        new QChartView(day_labels_piechart_chart_p_, this);
    day_labels_pie_chart_view_p_->setFixedHeight(chart_view_height_);
}

void lon::ChartsWidget::initWeekLabelsPieChart() {
    using namespace QtCharts;
    week_labels_piechart_chart_p_ =
        initPieChartSeries(lastweekdata_p_->label_data);

    week_labels_pie_chart_view_p_ =
        new QChartView(week_labels_piechart_chart_p_, this);
    week_labels_pie_chart_view_p_->setFixedHeight(chart_view_height_);
}

void lon::ChartsWidget::initMonthLabelsPieChart() {
    using namespace QtCharts;
    month_labels_piechart_chart_p_ =
        initPieChartSeries(lastmonthdata_p_->label_data);

    month_labels_pie_chart_view_p_ =
        new QChartView(month_labels_piechart_chart_p_, this);
    month_labels_pie_chart_view_p_->setFixedHeight(chart_view_height_);
}

void lon::ChartsWidget::initDayTargetsPieChart() {
    using namespace QtCharts;
    day_targets_piechart_chart_p_ =
        initPieChartSeries(todaydata_p_->target_data);
    day_targets_pie_chart_view_p_ =
        new QChartView(day_targets_piechart_chart_p_, this);
    day_targets_pie_chart_view_p_->setFixedHeight(chart_view_height_);
}

void lon::ChartsWidget::initWeekTargetsPieChart() {
    using namespace QtCharts;
    week_targets_piechart_chart_p_ =
        initPieChartSeries(lastweekdata_p_->target_data);
    week_targets_pie_chart_view_p_ =
        new QChartView(week_targets_piechart_chart_p_, this);
    week_targets_pie_chart_view_p_->setFixedHeight(chart_view_height_);
}

void lon::ChartsWidget::initMonthTargetsPieChart() {
    using namespace QtCharts;
    month_targets_piechart_chart_p_ =
        initPieChartSeries(lastmonthdata_p_->target_data);
    month_targets_pie_chart_view_p_ =
        new QChartView(month_targets_piechart_chart_p_, this);
    month_targets_pie_chart_view_p_->setFixedHeight(chart_view_height_);
}

void lon::ChartsWidget::initBestworkTimeChart() {
    using namespace QtCharts;
    QChart* chart = new QChart();
}

void lon::ChartsWidget::initFinishLinewidget() {
    finish_line_widget_p_ = new QWidget(this);
    finish_line_label_p_ = new QLabel(finish_line_widget_p_);
    finish_line_combobox_p_ = new QComboBox(finish_line_widget_p_);
    finish_line_layout_p_ = new QGridLayout(finish_line_widget_p_);

    finish_line_combobox_p_->addItem(QString("今日"));
    finish_line_combobox_p_->addItem((QString("过去七天")));
    finish_line_combobox_p_->addItem((QString("过去三十天")));

    finish_line_label_p_->setText(QString("完成番茄个数"));

    initDayFinishedLineChart();

    finish_line_layout_p_->addWidget(finish_line_combobox_p_,
                                     0,
                                     0,
                                     1,
                                     1,
                                     Qt::AlignRight);
    finish_line_layout_p_->addWidget(finish_line_label_p_,
                                     0,
                                     1,
                                     1,
                                     1,
                                     Qt::AlignLeft);
    finish_line_layout_p_->addWidget(day_finish_line_chart_view_p_, 1, 0, 1, 2);

    list_widget_p_->addWidget(finish_line_widget_p_);
}

void lon::ChartsWidget::initFinishedTimeLinewidget() {
    finishedtime_line_widget_p_ = new QWidget(this);
    finishedtime_line_label_p_ = new QLabel(finishedtime_line_widget_p_);
    finishedtime_line_combobox_p_ = new QComboBox(finishedtime_line_widget_p_);
    finishedtime_line_layout_p_ = new QGridLayout(finishedtime_line_widget_p_);

    finishedtime_line_combobox_p_->addItem(QString("今日"));
    finishedtime_line_combobox_p_->addItem(
        (QString("过去七天")));
    finishedtime_line_combobox_p_->addItem(
        (QString("过去三十天")));

    finishedtime_line_label_p_->setText(QString("完成时间"));

    initDayFinishedTimeLineChart();

    finishedtime_line_layout_p_->addWidget(finishedtime_line_combobox_p_,
                                           0,
                                           0,
                                           1,
                                           1,
                                           Qt::AlignRight);
    finishedtime_line_layout_p_->addWidget(finishedtime_line_label_p_,
                                           0,
                                           1,
                                           1,
                                           1,
                                           Qt::AlignLeft);
    finishedtime_line_layout_p_->addWidget(day_finishedtime_line_chart_view_p_,
                                           1,
                                           0,
                                           1,
                                           2);

    list_widget_p_->addWidget(finishedtime_line_widget_p_);
}

void lon::ChartsWidget::initLabelsPieWidget() {
    label_pie_widget_p_ = new QWidget(this);
    label_pie_label_p_ = new QLabel(label_pie_widget_p_);
    label_pie_combobox_p_ = new QComboBox(label_pie_widget_p_);
    label_pie_layout_p_ = new QGridLayout(label_pie_widget_p_);

    label_pie_combobox_p_->addItem(QString("今日"));
    label_pie_combobox_p_->addItem(QString("过去七天"));
    label_pie_combobox_p_->addItem(QString("过去三十天"));
    label_pie_label_p_->setText(QString("标签"));

    initDayLabelsPieChart();
    day_labels_pie_chart_view_p_->setFixedHeight(500);

    label_pie_layout_p_->addWidget(label_pie_combobox_p_, 0, 0, Qt::AlignRight);
    label_pie_layout_p_->addWidget(label_pie_label_p_, 0, 1, Qt::AlignLeft);
    label_pie_layout_p_->addWidget(day_labels_pie_chart_view_p_, 1, 0, 1, 2);

    list_widget_p_->addWidget(label_pie_widget_p_);
}

void lon::ChartsWidget::initTargetsPieWidget() {
    target_pie_widget_p_ = new QWidget(this);
    target_pie_label_p_ = new QLabel(target_pie_widget_p_);
    target_pie_combobox_p_ = new QComboBox(target_pie_widget_p_);
    target_pie_layout_p_ = new QGridLayout(target_pie_widget_p_);

    target_pie_combobox_p_->addItem(QString("今日"));
    target_pie_combobox_p_->addItem(QString("过去七天"));
    target_pie_combobox_p_->addItem(QString("过去30天"));
    target_pie_label_p_->setText(QString("完成的目标情况"));

    initDayTargetsPieChart();
    day_targets_pie_chart_view_p_->setFixedHeight(500);

    target_pie_layout_p_->addWidget(target_pie_combobox_p_,
                                    0,
                                    0,
                                    1,
                                    1,
                                    Qt::AlignRight);
    target_pie_layout_p_->addWidget(target_pie_label_p_,
                                    0,
                                    1,
                                    1,
                                    1,
                                    Qt::AlignLeft);
    target_pie_layout_p_->addWidget(day_targets_pie_chart_view_p_, 1, 0, 1, 2);

    list_widget_p_->addWidget(target_pie_widget_p_);
}

void lon::ChartsWidget::initBestworkTimeWidget() {
}

lon::ChartsWidget::ChartsWidget(
    std::shared_ptr<tomato_clock::TodayData> todaydata_p,
    std::shared_ptr<tomato_clock::LastWeekData> lastweekdata_p,
    std::shared_ptr<tomato_clock::LastMonthData> lastmonthdata_p,
    QWidget* parent)
    : QWidget(parent),
      todaydata_p_(todaydata_p),
      lastweekdata_p_(lastweekdata_p),
      lastmonthdata_p_(lastmonthdata_p) {
    using namespace QtCharts;
    layout_p_ = new QVBoxLayout(this);
    list_widget_p_ = new ListWidget(this);

    day_finish_line_chart_view_p_ = nullptr;
    week_finish_line_chart_view_p_ = nullptr;
    month_finish_line_chart_view_p_ = nullptr;

    week_finishedtime_line_chart_view_p_ = nullptr;
    month_finishedtime_line_chart_view_p_ = nullptr;
    day_finishedtime_line_chart_view_p_ = nullptr;

    day_labels_pie_chart_view_p_ = nullptr;
    week_labels_pie_chart_view_p_ = nullptr;
    month_labels_pie_chart_view_p_ = nullptr;
    day_targets_pie_chart_view_p_ = nullptr;
    week_targets_pie_chart_view_p_ = nullptr;
    month_targets_pie_chart_view_p_ = nullptr;
    bestworktime_chart_view_p_ = nullptr;

    finished_day_line_chart_p_ = nullptr;
    finished_week_line_chart_p_ = nullptr;
    finished_month_line_chart_p_ = nullptr;

    finishedtime_day_line_chart_p_ = nullptr;
    finishedtime_week_line_chart_p_ = nullptr;
    finishedtime_month_line_chart_p_ = nullptr;

    day_labels_piechart_chart_p_ = nullptr;
    week_labels_piechart_chart_p_ = nullptr;
    month_labels_piechart_chart_p_ = nullptr;
    day_targets_piechart_chart_p_ = nullptr;
    week_targets_piechart_chart_p_ = nullptr;
    month_targets_piechart_chart_p_ = nullptr;

    close_button_p_ = new Button(this);
    close_button_p_->setFixedSize(30, 30);
    close_button_p_->setToolTip(QString("返回"));

    close_button_p_->setFlat(true);
    close_button_p_->setStyleSheet("border:none");
    close_button_p_->setNormal(new QIcon(":/icon/Icons/close_normal.png"));
    close_button_p_->setFocus(new QIcon(":/icon/Icons/close_focus.png"));
    close_button_p_->setPressed(new QIcon(":/icon/Icons/close_pressed.png"));

    initFinishLinewidget();
    initFinishedTimeLinewidget();
    initLabelsPieWidget();
    initTargetsPieWidget();

    list_widget_p_->setHorizontalScrollBarVisible(true);
    list_widget_p_->setVerticalScrollBarVisible(false);
    layout_p_->addWidget(close_button_p_, 0, Qt::AlignRight);
    layout_p_->addWidget(list_widget_p_);
    this->setLayout(layout_p_);

    connect(close_button_p_,
            SIGNAL(clicked()),
            this,
            SIGNAL(closeButtonClicked()));
    connect(finish_line_combobox_p_,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(finishLineWidgetSwitchEvent(int)));
    connect(finishedtime_line_combobox_p_,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(finishedTimeLineWidgetSwitchEvent(int)));
    connect(target_pie_combobox_p_,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(targetsPieWidgetSwitchEvent(int)));
    connect(label_pie_combobox_p_,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(labelsPieWidgetSwitchEvent(int)));
}

lon::ChartsWidget::~ChartsWidget() {
    delete day_finish_line_chart_view_p_;
    delete week_finish_line_chart_view_p_;
    delete month_finish_line_chart_view_p_;
    delete week_finishedtime_line_chart_view_p_;
    delete month_finishedtime_line_chart_view_p_;
    delete day_finishedtime_line_chart_view_p_;
    delete day_labels_pie_chart_view_p_;
    delete week_labels_pie_chart_view_p_;
    delete month_labels_pie_chart_view_p_;
    delete day_targets_pie_chart_view_p_;
    delete week_targets_pie_chart_view_p_;
    delete month_targets_pie_chart_view_p_;
    delete bestworktime_chart_view_p_;
}

void lon::ChartsWidget::finishLineWidgetSwitchEvent(int index) {
    QWidget* p;
    int i;
    switch (index) {
        case 0: // today
            // remove widget at index 2 and setvisible false.
            finish_line_layout_p_->takeAt(2)->widget()->setVisible(false);
            day_finish_line_chart_view_p_->setVisible(true);
            finish_line_layout_p_->addWidget(day_finish_line_chart_view_p_,
                                             1,
                                             0,
                                             1,
                                             2);
            break;
        case 1: // last week
            if (!week_finish_line_chart_view_p_)
                initWeekFinishedLineChart();
            finish_line_layout_p_->takeAt(2)->widget()->setVisible(false);
            week_finish_line_chart_view_p_->setVisible(true);
            // day_finish_line_chart_view_p_->setVisible(false);
            finish_line_layout_p_->addWidget(week_finish_line_chart_view_p_,
                                             1,
                                             0,
                                             1,
                                             2);
            break;
        case 2: // last month
            if (!month_finish_line_chart_view_p_)
                initMonthFinishedLineChart();
            finish_line_layout_p_->takeAt(2)->widget()->setVisible(false);
            month_finish_line_chart_view_p_->setVisible(true);
            finish_line_layout_p_->addWidget(month_finish_line_chart_view_p_,
                                             1,
                                             0,
                                             1,
                                             2);
            break;
        default:
            qWarning() << "here should never be exec";
    }
}

void lon::ChartsWidget::finishedTimeLineWidgetSwitchEvent(int index) {
    switch (index) {
        case 0: // last year

            finishedtime_line_layout_p_->takeAt(2)->widget()->setVisible(false);
            day_finishedtime_line_chart_view_p_->setVisible(true);
            finishedtime_line_layout_p_->addWidget(
                day_finishedtime_line_chart_view_p_,
                1,
                0,
                1,
                2);
            break;
        case 1: // last week
            // remove widget at index 2 and setvisible false.
            if (!week_finishedtime_line_chart_view_p_)
                initWeekFinishedTimeLineChart();
            finishedtime_line_layout_p_->takeAt(2)->widget()->setVisible(false);
            week_finishedtime_line_chart_view_p_->setVisible(true);
            finishedtime_line_layout_p_->addWidget(
                week_finishedtime_line_chart_view_p_,
                1,
                0,
                1,
                2);
            break;
        case 2: // last month
            if (!month_finishedtime_line_chart_view_p_)
                initMonthFinishedTimeLineChart();
            finishedtime_line_layout_p_->takeAt(2)->widget()->setVisible(false);
            month_finishedtime_line_chart_view_p_->setVisible(true);
            finishedtime_line_layout_p_->addWidget(
                month_finishedtime_line_chart_view_p_,
                1,
                0,
                1,
                2);
            break;

        default:
            qWarning() << "here should never be exec";
    }
}

void lon::ChartsWidget::labelsPieWidgetSwitchEvent(int index) {
    switch (index) {
        case 0: // today
            label_pie_layout_p_->takeAt(2)->widget()->setVisible(false);
            day_labels_pie_chart_view_p_->setVisible(true);
            label_pie_layout_p_->addWidget(day_labels_pie_chart_view_p_,
                                           1,
                                           0,
                                           1,
                                           2);
            break;
        case 1: // last week
            if (!week_labels_pie_chart_view_p_)
                initWeekLabelsPieChart();
            label_pie_layout_p_->takeAt(2)->widget()->setVisible(false);
            week_labels_pie_chart_view_p_->setVisible(true);
            label_pie_layout_p_->addWidget(week_labels_pie_chart_view_p_,
                                           1,
                                           0,
                                           1,
                                           2);
            break;
        case 2: // last month
            if (!month_labels_pie_chart_view_p_)
                initMonthLabelsPieChart();
            label_pie_layout_p_->takeAt(2)->widget()->setVisible(false);
            month_labels_pie_chart_view_p_->setVisible(true);
            label_pie_layout_p_->addWidget(month_labels_pie_chart_view_p_,
                                           1,
                                           0,
                                           1,
                                           2);
            break;
    }
}

void lon::ChartsWidget::targetsPieWidgetSwitchEvent(int index) {
    switch (index) {
        case 0: // today
            target_pie_layout_p_->takeAt(2)->widget()->setVisible(false);
            day_targets_pie_chart_view_p_->setVisible(true);
            target_pie_layout_p_->addWidget(day_targets_pie_chart_view_p_,
                                            1,
                                            0,
                                            1,
                                            2);
            break;
        case 1: // last week
            if (!week_targets_pie_chart_view_p_)
                initWeekTargetsPieChart();
            target_pie_layout_p_->takeAt(2)->widget()->setVisible(false);
            week_targets_pie_chart_view_p_->setVisible(true);
            target_pie_layout_p_->addWidget(week_targets_pie_chart_view_p_,
                                            1,
                                            0,
                                            1,
                                            2);
            break;
        case 2: // last month
            if (!month_targets_pie_chart_view_p_)
                initMonthTargetsPieChart();
            target_pie_layout_p_->takeAt(2)->widget()->setVisible(false);
            month_targets_pie_chart_view_p_->setVisible(true);
            target_pie_layout_p_->addWidget(month_targets_pie_chart_view_p_,
                                            1,
                                            0,
                                            1,
                                            2);
            break;
    }
}
