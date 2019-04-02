#pragma once

#include <QString>
#include <algorithm>
#include <utility>
#include <vector>

#include "LonTypeDefines.h"

namespace lon {
namespace tomato_clock {
template <unsigned int len_num> struct ChartDataBase {
    // 在每个时间段完成的番茄个数(比如显示是天的话,
    // 那就是每个小时完成的番茄的个数).
    uint16_t *time_data_p;

    unsigned int                         length;
    std::vector<std::pair<QString, int>> target_data;
    std::vector<std::pair<QString, int>> label_data;

    ChartDataBase()
        : length(len_num) {
        time_data_p = new uint16_t[ length ]{};
    }

    ChartDataBase(const ChartDataBase &chart_data_base)
        : target_data(chart_data_base.target_data)
        , label_data(chart_data_base.label_data) {
        length = chart_data_base.length;

        time_data_p = new uint16_t[ length ]{};
        std::copy(chart_data_base.time_data_p,
                  chart_data_base.time_data_p + chart_data_base.length,
                  time_data_p);
    }

    ChartDataBase(ChartDataBase &&chart_data_base)
        : target_data(std::move(chart_data_base.target_data))
        , label_data(std::move(chart_data_base.label_data)) {
        length = chart_data_base.length;

        time_data_p                 = chart_data_base.time_data_p;
        chart_data_base.time_data_p = nullptr;
    }

    ~ChartDataBase() { delete[] time_data_p; }
};

template <unsigned int len_num>
struct ChartDataWithTotalTime : public ChartDataBase<len_num> {
    uint16_t *total_time_p;

    ChartDataWithTotalTime() {
        total_time_p = new uint16_t[ ChartDataBase<len_num>::length ]{};
    }

    ChartDataWithTotalTime(const ChartDataWithTotalTime &data)
        : ChartDataBase<len_num>::ChartDataBase(data) {
        total_time_p = new uint16_t[ ChartDataBase<len_num>::length ]{};
        std::copy(data.total_time_p, data.total_time_p + data.length,
                  total_time_p);
    }

    ChartDataWithTotalTime(ChartDataWithTotalTime &&data)
        : ChartDataBase<len_num>::ChartDataBase(std::move(data)) {
        total_time_p      = data.total_time_p;
        data.total_time_p = nullptr;
    }

    ~ChartDataWithTotalTime() { delete[] total_time_p; }
};

// clock chart 所需的每日数据.
using TodayData = ChartDataWithTotalTime<24>;
// clock chart 所需的每周数据.
using LastWeekData = ChartDataWithTotalTime<7>;
// clock chart 所需的每月数据.
// 取每个月天数可能的最大值.
using LastMonthData = ChartDataWithTotalTime<31>;
// clock chart 所需的每年数据.
// 取每年天数可能的最大值.
using LastYearData = ChartDataWithTotalTime<366>;

#if 0
struct TodayData {
    uint16_t *                           time_data_p;
    unsigned int                         length;
    std::vector<std::pair<QString, int>> target_data;
    std::vector<std::pair<QString, int>> label_data;

    TodayData() {
        length      = 24;
        time_data_p = new uint16_t[ length ]{};
    }

    TodayData(const TodayData &data) {
        qDebug() << "copy constructor";
        length      = 24;
        time_data_p = data.time_data_p;
    }

    TodayData(TodayData &&data)
        : time_data_p(nullptr) {
        qDebug() << "move constructor";
        time_data_p      = data.time_data_p;
        data.time_data_p = nullptr;
    }

    ~TodayData() { delete[] time_data_p; }
};

struct LastWeekData {
    uint16_t *                           time_data_p;
    uint16_t *                           worktime_data_p;
    unsigned int                         length;
    std::vector<std::pair<QString, int>> target_data;
    std::vector<std::pair<QString, int>> label_data;

    LastWeekData() {
        length          = 7;
        time_data_p     = new uint16_t[ length ]();
        worktime_data_p = new uint16_t[ length ]();
    }

    ~LastWeekData() {
        // delete worktime_data_p;
        // delete []time_data_p;
    }
};

struct LastMonthData {
    uint16_t *                           time_data_p;
    uint16_t *                           worktime_data_p;
    unsigned int                         length;
    std::vector<std::pair<QString, int>> target_data;
    std::vector<std::pair<QString, int>> label_data;

    LastMonthData() {
        //这里取length的可能的最大值.
        length      = 31;
        time_data_p = new uint16_t[ length ];
    }

    ~LastMonthData() {
        delete worktime_data_p;
        delete time_data_p;
    }
};

struct LastYearData {
    uint16_t *                           time_data_p;
    uint16_t *                           worktime_data_p;
    unsigned int                         length;
    std::vector<std::pair<QString, int>> target_data;
    std::vector<std::pair<QString, int>> label_data;

    LastYearData() {
        //取可能的最大值.
        length      = 366;
        time_data_p = new uint16_t[ length ];
    }

    ~LastYearData() {
        delete worktime_data_p;
        time_data_p;
    }
};
#endif
} // namespace tomato_clock
} // namespace lon