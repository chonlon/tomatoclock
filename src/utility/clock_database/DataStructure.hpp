#pragma once

#include <QString>
#include <algorithm>
#include <utility>
#include <vector>
#include <array>

#include "LonTypeDefines.h"

namespace lon {
namespace tomato_clock {
template <size_t len_num>
struct ChartDataBase {
    // 在每个时间段完成的番茄个数(比如显示是天的话,
    // 那就是每个小时完成的番茄的个数).
    std::array<uint16_t, len_num> time_data_p{};
    std::vector<std::pair<QString, int>> target_data;
    std::vector<std::pair<QString, int>> label_data;

    ChartDataBase() = default;

    ChartDataBase(const ChartDataBase& chart_data_base)
        : target_data(chart_data_base.target_data),
          label_data(chart_data_base.label_data),
          time_data_p(chart_data_base.time_data_p) {
    }

    ChartDataBase(ChartDataBase&& chart_data_base)
        : target_data(std::move(chart_data_base.target_data)),
          label_data(std::move(chart_data_base.label_data)),
          time_data_p(std::move(chart_data_base.time_data_p)) {
        ;
    }

    ~ChartDataBase() = default;
};

template <size_t len_num>
struct ChartDataWithTotalTime : public ChartDataBase<len_num> {
    std::array<uint16_t, len_num> total_time_p{};

    ChartDataWithTotalTime() = default;

    ChartDataWithTotalTime(const ChartDataWithTotalTime& data)
        : ChartDataBase<len_num>::ChartDataBase(data),
          total_time_p(data.total_time_p) {
    }

    ChartDataWithTotalTime(ChartDataWithTotalTime&& data)
        : ChartDataBase<len_num>::ChartDataBase(std::move(data)),
          total_time_p(std::move(data.total_time_p)) {
    }

    ~ChartDataWithTotalTime() = default;
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
}  // namespace tomato_clock
}  // namespace lon
