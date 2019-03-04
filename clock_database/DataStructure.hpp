#pragma once

#include <QString>
#include <vector>
#include <utility>

#include "LonTypeDefines.h"

namespace lon {
namespace tomato_clock {
struct TodayData {
    uint16_t *time_data_p;
    unsigned int length;
    std::vector<std::pair<QString, int>> target_data;
    std::vector<std::pair<QString, int>> label_data;

    TodayData() {
        length = 24;
        time_data_p = new uint16_t[length];
    }

    ~TodayData() {
        delete time_data_p;
    }
};

struct LastWeekData {
    uint16_t *time_data_p;
    std::vector<std::pair<QString, int>> target_data;
    std::vector<std::pair<QString, int>> label_data;

    LastWeekData() {
        time_data_p = new uint16_t[7];
    }

    ~LastWeekData() {
        delete time_data_p;
    }
};


struct LastMonthData {
    uint16_t *time_data_p;
    std::vector<std::pair<QString, int>> target_data;
    std::vector<std::pair<QString, int>> label_data;

    LastMonthData() {
        time_data_p = new uint16_t[30];
    }

    ~LastMonthData() {
        delete time_data_p;
    }
};


struct LastYearData {
    uint16_t *time_data_p;
    std::vector<std::pair<QString, int>> target_data;
    std::vector<std::pair<QString, int>> label_data;

    LastYearData() {
        time_data_p = new uint16_t[12];
    }

    ~LastYearData() {
        delete time_data_p;
    }
};

}
}
