﻿#pragma once

#include <QtSql>
#include <exception>
#include <list>
#include <vector>

#include "DataStructure.hpp"
#include "LonTypeDefines.h"


namespace lon {
/*!
 * \class ClockSql
 *
 * \brief 封装番茄钟相关数据库操作, 只允许存在一个Sql对象. 此类使用单例模式.
 *
 * \author LON
 */
class ClockSql {
private:
    QSqlDatabase sql_;
    QSqlQuery* query_;

    /// <summary> 执行没有TargetsTable时的初始化动作 </summary>
    void initTargetsTable() {
        bool tableExists = query_->exec("select count(*) from targets where TargetName = 'table'");
        if (!tableExists) {
            query_->exec(
                "CREATE TABLE targets (TargetId INT PRIMARY KEY, "
                "TargetName VARCHAR (50) UNIQUE, LabelName  VARCHAR "
                "(50) REFERENCES labels (LabelName));");
        }
    }

    /// <summary> 执行没有LabelsTable时的初始化动作 </summary>
    void initLabelsTable() {
        bool tableExists = query_->exec("select count(*) from labels where LabelName = 'table'");
        if (!tableExists) {
            query_->exec("CREATE TABLE labels (LabelName VARCHAR (50) PRIMARY KEY);");
        }
    }

    /// <summary> 执行没有FinishedTomatoTable时的初始化动作 </summary>
    void initFinishedTomatoTable() {
        bool tableExists = query_->exec("select count(*) from finishedtomato where name = 'table'");
        if (!tableExists) {
            query_->exec(
                "CREATE TABLE finishedtomato (TomatoId   INT  PRIMARY "
                "KEY, TargetId   INT  REFERENCES targets (TargetId), "
                "DuringTime INT, FinishTime DATETIME);");
        }
    }

    /// <summary> 获取在过去的数天(days)内, 番茄工作总时间. </summary>
    uint32_t getTotalTimeInDays(uint8_t days) {
        uint32_t result;

        query_->exec(
            "SELECT SUM(DuringTime)\
						 FROM finishedtomato\
						WHERE julianday('now') - julianday(FinishTime) <" +
            QString::number(days) + ";");

        result = static_cast<uint32_t>(query_->value(0).toInt());

        return result;
    }

    ClockSql() : sql_(QSqlDatabase::addDatabase("QSQLITE")) {
        sql_.setDatabaseName("ClockSql.db");
        if (!sql_.open())
            throw std::logic_error("database cannot be openned");
        query_ = new QSqlQuery(sql_);
        initLabelsTable();
        initTargetsTable();
        initFinishedTomatoTable();
    }

public:
    ~ClockSql() {
        delete query_;
    }

    // Clock 工厂方法.
    static ClockSql* Get() {
        static ClockSql* instance_ = nullptr;
        if (instance_ == nullptr)
            instance_ = new ClockSql();
        return instance_;
    }

    // a tomato have just finished
    void addAFinishedTomato(uint8_t duringtime, QString label, QString target) {
        query_->prepare(
            "INSERT INTO finishedtomato(TomatoId, TargetId, DuringTime, "
            "FinishTime) select MAX(finishedtomato.TomatoId) + 1 as id, "
            "targets.TargetId, :during , DateTime('now', 'localtime') from "
            "finishedtomato , targets where TargetName = :target and LabelName "
            "= :label");
        query_->bindValue(":during", QString::number(duringtime));
        query_->bindValue(":target", target);
        query_->bindValue(":label", label);
        query_->exec();
    }

    void addLabel(const QString& label_name) {
        query_->prepare("INSERT INTO labels VALUES (:label)");
        query_->bindValue(":label", label_name);
        query_->exec();
    }

    void deleteLabel(const QString& label_name) {
        query_->prepare("DELETE FROM labels WHERE LabelName = :label ");
        query_->bindValue(":label", label_name);
        query_->exec();
    }

    void deleteTarget(const QString& target_name) {
        query_->prepare("DELETE FROM targets WHERE TargetName = :target ");
        query_->bindValue(":target", target_name);
        query_->exec();
    }

    void addTarget(const QString& label_name, const QString& target_name) {
        query_->prepare(
            "INSERT INTO targets SELECT max(targets.TargetId) + 1 "
            "AS id, :label, :target FROM targets");
        query_->bindValue(":label", label_name);
        query_->bindValue(":target", target_name);
        query_->exec();
    }

    /// <summary> 获取过去一周的番茄完成的情况. </summary>
    /// <returns> 以TodayData返回结果, 包括时间分布,将target分布, label分布
    /// </returns>
    tomato_clock::TodayData getTodayData() {
        using namespace tomato_clock;
        TodayData data;
        // 获取今天的每个小时完成的番茄数量.
        query_->exec(
            "SELECT hour, "
            "count(hour)  "
            "FROM ( "
            "SELECT strftime('%H', FinishTime) AS hour "
            "FROM finishedtomato "
            "WHERE date('now', '-1 day') < date(FinishTime)  "
            ") "
            "GROUP BY hour "
            "ORDER BY hour; ");

        while (query_->next()) {
            data.time_data_p[query_->value(0).toInt()] =
                static_cast<uint16_t>(query_->value(1).toInt());
        }

        query_->exec(
            "SELECT time, "
            "SUM(DuringTime) "
            "FROM ( "
            "SELECT strftime('%H', FinishTime) AS time, DuringTime "
            "FROM finishedtomato "
            "WHERE date('now', '-1 day', 'localtime') < date(FinishTime) "
            ")"
            "GROUP BY time "
            "ORDER BY time;");
        while (query_->next()) {
            data.total_time_p[query_->value(0).toInt()] =
                static_cast<uint16_t>(query_->value(1).toInt());
        }
        //获取今天完成的番茄的target情况
        query_->exec(
            "SELECT targetname, "
            "count(targetname)  "
            "FROM ( "
            "SELECT targets.TargetName AS targetname "
            "FROM finishedtomato, "
            "targets "
            "WHERE date('now', '-1 day', 'localtime') < date(FinishTime) AND  "
            "finishedtomato.TargetId = targets.TargetId "
            ") "
            "GROUP BY targetname "
            "ORDER BY targetname; ");

        while (query_->next()) {
            data.target_data.push_back(
                std::make_pair(query_->value(0).toString(), query_->value(1).toInt()));
        }
        //获取今天完成的番茄的label数据
        query_->exec(
            "SELECT labelname,"
            "count(labelname) "
            "FROM ("
            "SELECT targets.LabelName AS labelname "
            "FROM finishedtomato,"
            "targets "
            "WHERE date('now', '-1 day','localtime') < date(FinishTime) AND "
            "finishedtomato.TargetId = targets.TargetId"
            ") "
            "GROUP BY labelname "
            "ORDER BY labelname; ");

        while (query_->next()) {
            data.label_data.push_back(
                std::make_pair(query_->value(0).toString(), query_->value(1).toInt()));
        }
        return data;
    }

    tomato_clock::LastWeekData getLastWeekData() {
        using namespace tomato_clock;
        LastWeekData data;
        // 获取过去七天的每天完成的番茄数量.
        query_->exec(
            "SELECT time, "
            "count(time) "
            "FROM ("
            "SELECT julianday('now', 'localtime', 'start of day') - "
            "julianday(FinishTime, 'start of day') AS time "
            "FROM finishedtomato "
            "WHERE date('now', '-7 day', 'localtime') < date(FinishTime) "
            ")"
            "GROUP BY time "
            "ORDER BY time;");
        while (query_->next()) {
            data.time_data_p[query_->value(0).toInt()] =
                static_cast<uint16_t>(query_->value(1).toInt());
        }

        // 获取过去七天每天完成的总时间
        query_->exec(
            "SELECT time, "
            "SUM(DuringTime) "
            "FROM ( "
            "SELECT julianday('now', 'localtime', 'start of day') - "
            "julianday(FinishTime, 'start of day') AS time, DuringTime "
            "FROM finishedtomato "
            "WHERE date('now', '-7 day', 'localtime') < date(FinishTime) "
            ")"
            "GROUP BY time "
            "ORDER BY time;");
        while (query_->next()) {
            data.total_time_p[query_->value(0).toInt()] =
                static_cast<uint16_t>(query_->value(1).toInt());
        }
        //获取本周完成的番茄的target情况
        query_->exec(
            "SELECT targetname, "
            "count(targetname)  "
            "FROM ( "
            "SELECT targets.TargetName AS targetname "
            "FROM finishedtomato, "
            "targets "
            "WHERE date('now', '-7 day', 'localtime') < date(FinishTime) AND  "
            "finishedtomato.TargetId = targets.TargetId "
            ") "
            "GROUP BY targetname "
            "ORDER BY targetname; ");

        while (query_->next()) {
            data.target_data.push_back(
                std::make_pair(query_->value(0).toString(), query_->value(1).toInt()));
        }
        //获取本周完成的番茄的label数据
        query_->exec(
            "SELECT labelname,"
            "count(labelname) "
            "FROM ("
            "SELECT targets.LabelName AS labelname "
            "FROM finishedtomato,"
            "targets "
            "WHERE date('now', '-7 day', 'localtime') < date(FinishTime) AND "
            "finishedtomato.TargetId = targets.TargetId"
            ") "
            "GROUP BY labelname "
            "ORDER BY labelname; ");

        while (query_->next()) {
            data.label_data.push_back(
                std::make_pair(query_->value(0).toString(), query_->value(1).toInt()));
        }
        return data;
    }

    /// <summary> 获取过去一月的番茄完成的情况. </summary>
    /// <returns> 以QString数组存储完成的番茄的日期的列表.格式为YYYY-MM-DD
    /// </returns>
    tomato_clock::LastMonthData getLastMonthData() {
        using namespace tomato_clock;
        LastMonthData data;
        // 获取本月的每天完成的番茄数量.
        query_->exec(
            "SELECT time, "
            "count(time) "
            "FROM ("
            "SELECT julianday('now', 'localtime', 'start of day') - "
            "julianday(FinishTime, 'start of day') AS time "
            "FROM finishedtomato "
            "WHERE date('now', '-30 day', 'localtime') < date(FinishTime) "
            ")"
            "GROUP BY time "
            "ORDER BY time;");

        while (query_->next()) {
            data.time_data_p[query_->value(0).toInt()] =
                static_cast<uint16_t>(query_->value(1).toInt());
        }

        // 获取过去七天每天完成的总时间
        query_->exec(
            "SELECT time, "
            "SUM(DuringTime) "
            "FROM ("
            "SELECT julianday('now', 'localtime', 'start of day') - "
            "julianday(FinishTime, 'start of day') AS time, DuringTime "
            "FROM finishedtomato "
            "WHERE date('now', '-30 day', 'localtime') < date(FinishTime) "
            ")"
            "GROUP BY time "
            "ORDER BY time;");
        // 此处如果数据库中存了超过当前时间的值, 会导致超过数据访问范围.
        while (query_->next()) {
            data.total_time_p[query_->value(0).toInt()] =
                static_cast<uint16_t>(query_->value(1).toInt());
        }

        //获取本月完成的番茄的target情况
        query_->exec(
            "SELECT targetname, "
            "count(targetname)  "
            "FROM ( "
            "SELECT targets.TargetName AS targetname "
            "FROM finishedtomato, "
            "targets "
            "WHERE date('now', '-30 day', 'localtime') < date(FinishTime) AND  "
            "finishedtomato.TargetId = targets.TargetId "
            ") "
            "GROUP BY targetname "
            "ORDER BY targetname; ");

        while (query_->next()) {
            data.target_data.push_back(
                std::make_pair(query_->value(0).toString(), query_->value(1).toInt()));
        }
        //获取本月完成的番茄的label数据
        query_->exec(
            "SELECT labelname,"
            "count(labelname) "
            "FROM ("
            "SELECT targets.LabelName AS labelname "
            "FROM finishedtomato,"
            "targets "
            "WHERE date('now', '-30 day','localtime') < date(FinishTime) AND "
            "finishedtomato.TargetId = targets.TargetId"
            ") "
            "GROUP BY labelname "
            "ORDER BY labelname; ");

        while (query_->next()) {
            data.label_data.push_back(
                std::make_pair(query_->value(0).toString(), query_->value(1).toInt()));
        }
        return data;
    }

    // TODO make last year a bit different.
    /// <summary> 获取过去一年的番茄完成的情况. </summary>
    /// <returns> 以QString数组存储完成的番茄的日期的列表.格式为YYYY-MM-DD
    /// </returns>
    std::vector<QString> getLastYearData() {
        std::vector<QString> result;
        query_->exec(
            "SELECT date(FinishTime) \
						FROM finishedtomato\
						WHERE date('now', '-1 year') < date(FinishTime);");
        while (query_->next()) {
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
    /// <param name: duration> 以duration为单位查找. eg: 月: 'month',
    /// 天:'day'</param>
    std::vector<int> getBestWorkTimeDesc(const QString& duration) {
        std::vector<int> result;
        query_->prepare(
            "SELECT DuringTime,"
            "strftime('%H', FinishTime) AS hours "
            "FROM ("
            "SELECT * "
            "FROM finishedtomato "
            "GROUP BY strftime('%H', FinishTime)"
            ")"
            "WHERE date('now', "
            ":duration) < date(FinishTime)"
            "ORDER BY DuringTime DESC;");
        query_->bindValue(":duration", "-1" + duration);
        query_->exec();
        while (query_->next()) {
            result.emplace_back(query_->value(0).toInt());
        }
        return result;
    }

    /// <summary>
    /// get all labels name order by name, return by QString
    /// </summary>
    std::list<QString> getAllLabels() {
        std::list<QString> result;
        query_->exec("SELECT LabelName FROM labels ORDER BY LabelName");
        while (query_->next()) {
            result.emplace_back(query_->value(0).toString());
        }
        return result;
    }

    QString getLabelByTarget() {
        return QString();
    }

    // get targets by label name.
    /// <summary>
    /// get all targets belong to label.
    /// </summary>
    /// <param name="label">label名字, 每个标签唯一, 当label可为空.</param>
    /// <returns>all targets' name.</returns>
    std::vector<QString> getTargetsByLabel(const QString& label) {
        std::vector<QString> result;
        if (label.isEmpty()) {
            query_->exec("SELECT TargetName FROM targets");
        } else {
            query_->exec("SELECT TargetName FROM targets WHERE LabelName =" + label);
        }
        while (query_->next()) {
            result.emplace_back(query_->value(0).toString());
        }
        return result;
    }

    /// <summary>
    /// get all labels name and target name pair order by label, return by
    /// std::pair.
    /// </summary>
    std::list<std::pair<QString, QString>> getAllTargetsAndLabels() {
        std::list<std::pair<QString, QString>> result;
        query_->exec("select LabelName, TargetName from targets order by LabelName");
        while (query_->next()) {
            result.push_back(
                std::make_pair(query_->value(0).toString(), query_->value(1).toString()));
        }
        return result;
    }

    bool targetExists(const QString& label, const QString& target) {
        query_->exec("select count(*) from targets where LabelName = " + label +
                     " and TargetName = " + target);
        return query_->value(0).toInt();
    }
};
}  // namespace lon
