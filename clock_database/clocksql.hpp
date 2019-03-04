#pragma once

#include <QtSql>
#include <exception>

#include "LonTypeDefines.h"
#include "DataStructure.hpp"
namespace lon {
    class ClockSql {
    private:
        QSqlDatabase sql_;
        QSqlQuery *query_;

        /// <summary> 执行没有TargetsTable时的初始化动作 </summary>
        void initTargetsTable() {
            bool tableExists = query_->exec("select count(*) from targets where TargetName = 'table'");
            if(!tableExists) {
                query_->exec("CREATE TABLE targets (\
                                 TargetId   INT          PRIMARY KEY,\
                                 TargetName VARCHAR (50) UNIQUE,\
                                 LabelName  VARCHAR (50) REFERENCES labels (LabelName)\
                             );");
            }
        }

        /// <summary> 执行没有LabelsTable时的初始化动作 </summary>
        void initLabelsTable() {
            bool tableExists = query_->exec("select count(*) from labels where LabelName = 'table'");
            if(!tableExists) {
                query_->exec("CREATE TABLE labels ( \
                                 LabelName VARCHAR (50) PRIMARY KEY \
                             );");
            }
        }

        /// <summary> 执行没有FinishedTomatoTable时的初始化动作 </summary>
        void initFinishedTomatoTable() {
            bool tableExists = query_->exec("select count(*) from finishedtomato where name = 'table'");
                        if(!tableExists) {
                            query_->exec("CREATE TABLE finishedtomato (\
                                             TomatoId   INT  PRIMARY KEY,\
                                             TargetId   INT  REFERENCES targets (TargetId),\
                                             DuringTime INT,\
                                             FinishTime DATETIME\
                                         );");
                        }
        }
        
        /// <summary> 获取在过去的数天(days)内, 番茄工作总时间. </summary>
        uint32_t getTotalTimeInDays(uint8_t days) {
            uint32_t result;
            
            query_->exec("SELECT SUM(DuringTime)\
                         FROM finishedtomato\
                        WHERE julianday('now') - julianday(FinishTime) <" + QString::number(days) + ";");
            
            result = static_cast<uint32_t>(query_->value(0).toInt());
                    
            return result;
        }
    public:
        ClockSql() :
            sql_(QSqlDatabase::addDatabase("QSQLITE")) {
            sql_.setDatabaseName("ClockSql.db");
            if(!sql_.open()) throw std::logic_error("database cannot be openned");
            query_ = new QSqlQuery(sql_);
            initLabelsTable();
            initTargetsTable();
            initFinishedTomatoTable();

            getLastWeekData();
        }

        /// <summary> 获取过去一周的番茄完成的情况. </summary>
        /// <returns> 以TodayData返回结果, 包括时间分布,将target分布, label分布 </returns>
        lon::tomato_clock::TodayData getTodayData() {
            using namespace lon::tomato_clock;
            TodayData data;
            // 获取今天的每个小时完成的番茄数量.
            query_->exec("SELECT hour,\
                         count(hour) \
                    FROM (\
                             SELECT datetime(FinishTime) AS time,\
                                    strftime('%H', FinishTime) AS day\
                               FROM finishedtomato\
                              WHERE date('now', '-1 day') < date(FinishTime) \
                         )\
                   GROUP BY hour\
                   ORDER BY hour;");

            while(query_->next()) {
                data.time_data_p[query_->value(0).toInt()] = static_cast<uint16_t>(query_->value(1).toInt());
            }
            //获取今天完成的番茄的target情况
            query_->exec("SELECT targetname,\
                         count(targetname),\
                    FROM (\
                             SELECT targets.TargetName AS targetname,\
                               FROM finishedtomato,\
                                    targets\
                              WHERE date('now', '-1 day') < date(FinishTime) AND \
                                    finishedtomato.TargetId = targets.TargetId\
                         );");


            while(query_->next()) {
                data.target_data.push_back(std::make_pair(query_->value(0).toString(), query_->value(1).toInt()));
            }
            //获取今天完成的番茄的label数据
            query_->exec("SELECT labelname,\
                         count(labelname) \
                    FROM (\
                             SELECT targets.LabelName AS labelname\
                               FROM finishedtomato,\
                                    targets\
                              WHERE date('now', '-1 day') < date(FinishTime) AND \
                                    finishedtomato.TargetId = targets.TargetId\
                         );");

            while(query_->next()) {
                data.label_data.push_back(std::make_pair(query_->value(0).toString(), query_->value(1).toInt()));
            }
            return data;
        }

        lon::tomato_clock::LastWeekData getLastWeekData() {
            using namespace lon::tomato_clock;
            LastWeekData data;
            // 获取本周的每天完成的番茄数量.
            query_->exec("SELECT day,\
                         count(day) \
                    FROM (\
                             SELECT datetime(FinishTime) AS time,\
                                    strftime('%d', FinishTime) AS day\
                               FROM finishedtomato\
                              WHERE date('now', '-7 day') < date(FinishTime) \
                         )\
                   GROUP BY day\
                   ORDER BY day;");


            while(query_->next()) {
                data.time_data_p[query_->value(0).toInt()] = static_cast<uint16_t>(query_->value(1).toInt());
            }
            //获取本周完成的番茄的target情况
            query_->exec("SELECT targetname,\
                         count(targetname),\
                    FROM (\
                             SELECT targets.TargetName AS targetname,\
                               FROM finishedtomato,\
                                    targets\
                              WHERE date('now', '-7 day') < date(FinishTime) AND \
                                    finishedtomato.TargetId = targets.TargetId\
                         );");


            while(query_->next()) {
                data.target_data.push_back(std::make_pair(query_->value(0).toString(), query_->value(1).toInt()));
            }
            //获取本周完成的番茄的label数据
            query_->exec("SELECT labelname,\
                         count(labelname) \
                    FROM (\
                             SELECT targets.LabelName AS labelname\
                               FROM finishedtomato,\
                                    targets\
                              WHERE date('now', '-7 day') < date(FinishTime) AND \
                                    finishedtomato.TargetId = targets.TargetId\
                         );");

            while(query_->next()) {
                data.label_data.push_back(std::make_pair(query_->value(0).toString(), query_->value(1).toInt()));
            }
            return data;
        }
        
        /// <summary> 获取过去一月的番茄完成的情况. </summary>
        /// <returns> 以QString数组存储完成的番茄的日期的列表.格式为YYYY-MM-DD </returns>
        lon::tomato_clock::LastMonthData getLastMonthData() {
            using namespace lon::tomato_clock;
            LastMonthData data;
            // 获取本周的每天完成的番茄数量.
            query_->exec("SELECT day,\
                         count(day) \
                    FROM (\
                             SELECT datetime(FinishTime) AS time,\
                                    strftime('%d', FinishTime) AS day\
                               FROM finishedtomato\
                              WHERE date('now', '-30 day') < date(FinishTime) \
                         )\
                   GROUP BY day\
                   ORDER BY day;");


            while(query_->next()) {
                data.time_data_p[query_->value(0).toInt()] = static_cast<uint16_t>(query_->value(1).toInt());
            }
            //获取本周完成的番茄的target情况
            query_->exec("SELECT targetname,\
                         count(targetname),\
                    FROM (\
                             SELECT targets.TargetName AS targetname,\
                               FROM finishedtomato,\
                                    targets\
                              WHERE date('now', '-30 day') < date(FinishTime) AND \
                                    finishedtomato.TargetId = targets.TargetId\
                         );");


            while(query_->next()) {
                data.target_data.push_back(std::make_pair(query_->value(0).toString(), query_->value(1).toInt()));
            }
            //获取本周完成的番茄的label数据
            query_->exec("SELECT labelname,\
                         count(labelname) \
                    FROM (\
                             SELECT targets.LabelName AS labelname\
                               FROM finishedtomato,\
                                    targets\
                              WHERE date('now', '-30 day') < date(FinishTime) AND \
                                    finishedtomato.TargetId = targets.TargetId\
                         );");

            while(query_->next()) {
                data.label_data.push_back(std::make_pair(query_->value(0).toString(), query_->value(1).toInt()));
            }
            return data;
        }
        
        //TODO make last year a bit different.
        /// <summary> 获取过去一年的番茄完成的情况. </summary>
        /// <returns> 以QString数组存储完成的番茄的日期的列表.格式为YYYY-MM-DD </returns>
        std::vector<QString> getLastYearData() {
            std::vector<QString> result;
            query_->exec("SELECT date(FinishTime) \
                        FROM finishedtomato\
                        WHERE date('now', '-1 year') < date(FinishTime);");
            while(query_->next()){
                result.emplace_back(query_->value(0).toString());
            }
            return result;
        }
        
        std::vector<int> getWorkTimeLastMouth() {
            return std::vector<int>();
        }
        
        std::vector<int> getWorkTimeLastYear() {
            return std::vector<int>();
        }

        /// <summary> 将某时间段的工作时段以降序的方式保存到数组中. </summary>
        /// <param name: duration> 以duration为单位查找. eg: 月: 'month', 天:'day'</param>
        std::vector<int> getBestWorkTimeDesc(QString duration) {
             std::vector<int> result;
             query_-> exec("SELECT DuringTime,\
                           strftime('%H', FinishTime) AS hours\
                      FROM (\
                               SELECT *\
                                 FROM finishedtomato \
                                 GROUP BY strftime('%H', FinishTime)\
                           )\
                    WHERE date('now', '-1" + duration + "') < date(FinishTime)\
                    ORDER BY DuringTime DESC;");
             while( query_->next()) {
                 result.emplace_back(query_->value(0).toInt());
             }
             return result;
        }
    };
}
