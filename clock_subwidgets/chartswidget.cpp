// encoded with gbk, cause QString::fromUtf8 doesn't work.
#include "chartswidget.h"
#include <QMessageBox>
#include <QValueAxis>
#include <algorithm>

QtCharts::QChart *lon::ChartsWidget::initLineChartSeries(
    uint16_t *data_array, unsigned int length, QString title /*= QString()*/) {
    using namespace QtCharts;
    //所有的chart的所有权会被被转移到chartview中, 所以不用担心这里会内存泄漏.
    QChart *chart = new QChart();
    chart->setTitle(title);
    // chart will take series's ownship.
    QLineSeries *series = new QLineSeries(chart);
    for (int i = 0; i < length; ++i) {
        series->append(i, data_array[ i ]);
    }
    chart->addSeries(series);

    //设置chart的导航线(axes)
    int _max = *std::max_element(data_array, data_array + length);
    //避免纵轴长度为零
    _max = std::max(2, _max);
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, _max);
    dynamic_cast<QValueAxis *>(chart->axes(Qt::Vertical).first())
        ->setTickCount(_max + 1);
    chart->axes(Qt::Horizontal).first()->setRange(0, std::max(length - 1, static_cast<unsigned int>(1)));
    dynamic_cast<QValueAxis *>(chart->axes(Qt::Horizontal).first())
        ->setTickCount(length);
    dynamic_cast<QValueAxis *>(chart->axes(Qt::Horizontal).first())
        ->setLabelFormat("%d");
    return chart;
}

QtCharts::QChart *lon::ChartsWidget::initPieChartSeries(
    std::vector<std::pair<QString, int>> labels_data,
    QString                              title /*= QString()*/) {
    using namespace QtCharts;
    QChart *chart = new QChart();
    chart->setTitle(title);
    QPieSeries *series = new QPieSeries(chart);
    for (int i = 0; i < labels_data.size(); ++i) {
        QPieSlice *slice =
            series->append(labels_data[ i ].first, labels_data[ i ].second);
        slice->setLabelVisible(true);
    }
    series->setPieSize(0.6);
    chart->addSeries(series);

    return chart;
}

void lon::ChartsWidget::initFinishedLineChart() {
    using namespace QtCharts;
    finished_day_line_chart_p_ =
        initLineChartSeries(todaydata_.time_data_p, todaydata_.length);
    finish_line_chart_view_p_ = new QChartView(finished_day_line_chart_p_);
}

void lon::ChartsWidget::initFinishedTimeLineChart() {
    using namespace QtCharts;
    finishedtime_week_line_chart_p_ =
        initLineChartSeries(lastweekdata_.total_time_p, lastweekdata_.length);
    finishedtime_line_chart_view_p_ =
        new QChartView(finishedtime_week_line_chart_p_);
}

void lon::ChartsWidget::initLabelsPieChart() {
    using namespace QtCharts;
    day_labels_piechart_chart_p_ = initPieChartSeries(todaydata_.label_data);

    day_labels_pie_chart_view_p_ =
        new QtCharts::QChartView(day_labels_piechart_chart_p_);
}

void lon::ChartsWidget::initTargetsPieChart() {
    using namespace QtCharts;
    day_targets_piechart_chart_p_ = initPieChartSeries(todaydata_.target_data);
    day_targets_pie_chart_view_p_ =
        new QtCharts::QChartView(day_targets_piechart_chart_p_);
}

void lon::ChartsWidget::initBestworkTimeChart() {
    using namespace QtCharts;
    QChart *chart = new QChart();
}

void lon::ChartsWidget::initFinishLinewidget() {
    finish_line_widget_p_   = new QWidget(this);
    finish_line_label_p_    = new QLabel(finish_line_widget_p_);
    finish_line_combobox_p_ = new QComboBox(finish_line_widget_p_);
    finish_line_layout_p_   = new QGridLayout(finish_line_widget_p_);

    finish_line_combobox_p_->addItem(QString::fromLocal8Bit("今日"));
    finish_line_combobox_p_->addItem((QString::fromLocal8Bit("过去七天")));
    finish_line_combobox_p_->addItem((QString::fromLocal8Bit("过去三十天")));

    finish_line_label_p_->setText(QString::fromLocal8Bit("完成番茄个数"));

    initFinishedLineChart();
    finish_line_chart_view_p_->setFixedHeight(500);

    finish_line_layout_p_->addWidget(finish_line_combobox_p_, 0, 0, 1, 1,
                                     Qt::AlignRight);
    finish_line_layout_p_->addWidget(finish_line_label_p_, 0, 1, 1, 1,
                                     Qt::AlignLeft);
    finish_line_layout_p_->addWidget(finish_line_chart_view_p_, 1, 0, 1, 2);

    list_widget_p_->addWidget(finish_line_widget_p_);
}

void lon::ChartsWidget::initFinishedTimeLinewidget() {
    finishedtime_line_widget_p_   = new QWidget(this);
    finishedtime_line_label_p_    = new QLabel(finishedtime_line_widget_p_);
    finishedtime_line_combobox_p_ = new QComboBox(finishedtime_line_widget_p_);
    finishedtime_line_layout_p_ = new QGridLayout(finishedtime_line_widget_p_);

    finishedtime_line_combobox_p_->addItem(
        (QString::fromLocal8Bit("过去七天")));
    finishedtime_line_combobox_p_->addItem(
        (QString::fromLocal8Bit("过去三十天")));
    finishedtime_line_combobox_p_->addItem(QString::fromLocal8Bit("上一年"));

    finishedtime_line_label_p_->setText(QString::fromLocal8Bit("完成时间"));

    initFinishedTimeLineChart();
    finishedtime_line_chart_view_p_->setFixedHeight(500);

    finishedtime_line_layout_p_->addWidget(finishedtime_line_combobox_p_, 0, 0,
                                           1, 1, Qt::AlignRight);
    finishedtime_line_layout_p_->addWidget(finishedtime_line_label_p_, 0, 1, 1,
                                           1, Qt::AlignLeft);
    finishedtime_line_layout_p_->addWidget(finishedtime_line_chart_view_p_, 1,
                                           0, 1, 2);

    list_widget_p_->addWidget(finishedtime_line_widget_p_);
}

void lon::ChartsWidget::initLabelsPieWidget() {
    label_pie_widget_p_   = new QWidget(this);
    label_pie_label_p_    = new QLabel(label_pie_widget_p_);
    label_pie_combobox_p_ = new QComboBox(label_pie_widget_p_);
    label_pie_layout_p_   = new QGridLayout(label_pie_widget_p_);

    label_pie_combobox_p_->addItem(QString::fromLocal8Bit("过去七天"));
    label_pie_combobox_p_->addItem(QString::fromLocal8Bit("过去三十天"));
    label_pie_combobox_p_->addItem(QString::fromLocal8Bit("上一年"));
    label_pie_label_p_->setText(QString::fromLocal8Bit("标签"));

    initLabelsPieChart();
    day_labels_pie_chart_view_p_->setFixedHeight(500);

    label_pie_layout_p_->addWidget(label_pie_combobox_p_, 0, 0, Qt::AlignRight);
    label_pie_layout_p_->addWidget(label_pie_label_p_, 0, 1, Qt::AlignLeft);
    label_pie_layout_p_->addWidget(day_labels_pie_chart_view_p_, 1, 0, 1, 2);

    list_widget_p_->addWidget(label_pie_widget_p_);
}

void lon::ChartsWidget::initTargetsPieWidget() {
    target_pie_widget_p_   = new QWidget(this);
    target_pie_label_p_    = new QLabel(target_pie_widget_p_);
    target_pie_combobox_p_ = new QComboBox(target_pie_widget_p_);
    target_pie_layout_p_   = new QGridLayout(target_pie_widget_p_);

    target_pie_combobox_p_->addItem(QString::fromLocal8Bit("过去七天"));
    target_pie_combobox_p_->addItem(QString::fromLocal8Bit("过去30天"));
    target_pie_combobox_p_->addItem(QString::fromLocal8Bit("上一年"));
    target_pie_label_p_->setText(QString::fromLocal8Bit("完成的目标情况"));

    initTargetsPieChart();
    day_targets_pie_chart_view_p_->setFixedHeight(500);

    target_pie_layout_p_->addWidget(target_pie_combobox_p_, 0, 0, 1, 1,
                                    Qt::AlignRight);
    target_pie_layout_p_->addWidget(target_pie_label_p_, 0, 1, 1, 1,
                                    Qt::AlignLeft);
    target_pie_layout_p_->addWidget(day_targets_pie_chart_view_p_, 1, 0, 1, 2);

    list_widget_p_->addWidget(target_pie_widget_p_);
}

void lon::ChartsWidget::initBestworkTimeWidget() {}

lon::ChartsWidget::ChartsWidget(lon::ClockSql *sql, QWidget *parent)
    : QWidget(parent)
    , sql_(sql)
    , todaydata_(sql_->getTodayData())
    , lastweekdata_(sql_->getLastWeekData())
    , lastmonthdata_(sql_->getLastMonthData()) {
    using namespace QtCharts;
    layout_p_      = new QVBoxLayout(this);
    list_widget_p_ = new lon::ListWidget(this);

    finish_line_chart_view_p_       = nullptr;
    finishedtime_line_chart_view_p_ = nullptr;
    day_labels_pie_chart_view_p_    = nullptr;
    week_labels_pie_chart_view_p_   = nullptr;
    month_labels_pie_chart_view_p_  = nullptr;
    day_targets_pie_chart_view_p_   = nullptr;
    week_targets_pie_chart_view_p_  = nullptr;
    month_targets_pie_chart_view_p_ = nullptr;
    bestworktime_chart_view_p_      = nullptr;

    finished_day_line_chart_p_   = nullptr;
    finished_week_line_chart_p_  = nullptr;
    finished_month_line_chart_p_ = nullptr;

    finishedtime_year_line_chart_p_  = nullptr;
    finishedtime_week_line_chart_p_  = nullptr;
    finishedtime_month_line_chart_p_ = nullptr;

    day_labels_piechart_chart_p_    = nullptr;
    week_labels_piechart_chart_p_   = nullptr;
    month_labels_piechart_chart_p_  = nullptr;
    day_targets_piechart_chart_p_   = nullptr;
    week_targets_piechart_chart_p_  = nullptr;
    month_targets_piechart_chart_p_ = nullptr;

    close_button_p_ = new lon::Button(this);
    close_button_p_->setFixedSize(30, 30);
    close_button_p_->setToolTip(QString::fromLocal8Bit("返回"));

    initFinishLinewidget();
    initFinishedTimeLinewidget();
    initLabelsPieWidget();
    initTargetsPieWidget();

    list_widget_p_->setHorizontalScrollBarVisible(true);
    list_widget_p_->setVerticalScrollBarVisible(false);
    layout_p_->addWidget(close_button_p_, 0, Qt::AlignRight);
    layout_p_->addWidget(list_widget_p_);
    this->setLayout(layout_p_);

    connect(close_button_p_, SIGNAL(clicked()), this,
            SIGNAL(closeButtonClicked()));
}

lon::ChartsWidget::~ChartsWidget() {
	delete finish_line_chart_view_p_;
	delete finishedtime_line_chart_view_p_;
	delete day_labels_pie_chart_view_p_;
	delete week_labels_pie_chart_view_p_;
	delete month_labels_pie_chart_view_p_;
	delete day_targets_pie_chart_view_p_;
	delete week_targets_pie_chart_view_p_;
	delete month_targets_pie_chart_view_p_;
	delete bestworktime_chart_view_p_;
}
