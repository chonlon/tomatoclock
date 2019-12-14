#pragma once

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
 * \brief ��װ������������ݿ����, ֻ��������һ��Sql����. ����ʹ�õ���ģʽ.
 *
 * \author LON
 */
class ClockSql {
  private:
	QSqlDatabase sql_;
	QSqlQuery *  query_;

	/// <summary> ִ��û��TargetsTableʱ�ĳ�ʼ������ </summary>
	void initTargetsTable() {
		bool tableExists = query_->exec(
			"select count(*) from targets where TargetName = 'table'");
		if (!tableExists) {
			query_->exec("CREATE TABLE targets (TargetId INT PRIMARY KEY, "
						 "TargetName VARCHAR (50) UNIQUE, LabelName  VARCHAR "
						 "(50) REFERENCES labels (LabelName));");
		}
	}

	/// <summary> ִ��û��LabelsTableʱ�ĳ�ʼ������ </summary>
	void initLabelsTable() {
		bool tableExists = query_->exec(
			"select count(*) from labels where LabelName = 'table'");
		if (!tableExists) {
			query_->exec(
				"CREATE TABLE labels (LabelName VARCHAR (50) PRIMARY KEY);");
		}
	}

	/// <summary> ִ��û��FinishedTomatoTableʱ�ĳ�ʼ������ </summary>
	void initFinishedTomatoTable() {
		bool tableExists = query_->exec(
			"select count(*) from finishedtomato where name = 'table'");
		if (!tableExists) {
			query_->exec("CREATE TABLE finishedtomato (TomatoId   INT  PRIMARY "
						 "KEY, TargetId   INT  REFERENCES targets (TargetId), "
						 "DuringTime INT, FinishTime DATETIME);");
		}
	}

	/// <summary> ��ȡ�ڹ�ȥ������(days)��, ���ѹ�����ʱ��. </summary>
	uint32_t getTotalTimeInDays(uint8_t days) {
		uint32_t result;

		query_->exec("SELECT SUM(DuringTime)\
						 FROM finishedtomato\
						WHERE julianday('now') - julianday(FinishTime) <" +
					 QString::number(days) + ";");

		result = static_cast<uint32_t>(query_->value(0).toInt());

		return result;
	}

	ClockSql()
		: sql_(QSqlDatabase::addDatabase("QSQLITE")) {
		sql_.setDatabaseName("ClockSql.db");
		if (!sql_.open()) throw std::logic_error("database cannot be openned");
		query_ = new QSqlQuery(sql_);
		initLabelsTable();
		initTargetsTable();
		initFinishedTomatoTable();
	}
public:
	~ClockSql() {
		delete query_;
	}

	// Clock ��������.
	static ClockSql *Get() {
		static ClockSql *instance_ = nullptr;
		if (instance_ == nullptr) instance_ = new ClockSql();
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

	void addLabel(const QString &label_name) {
		query_->prepare("INSERT INTO labels VALUES (:label)");
		query_->bindValue(":label", label_name);
		query_->exec();
	}

	void deleteLabel(const QString &label_name) {
		query_->prepare("DELETE FROM labels WHERE LabelName = :label ");
		query_->bindValue(":label", label_name);
		query_->exec();
	}

	void deleteTarget(const QString &target_name) {
		query_->prepare("DELETE FROM targets WHERE TargetName = :target ");
		query_->bindValue(":target", target_name);
		query_->exec();
	}

	void addTarget(const QString &label_name, const QString &target_name) {
		query_->prepare("INSERT INTO targets SELECT max(targets.TargetId) + 1 "
						"AS id, :label, :target FROM targets");
		query_->bindValue(":label", label_name);
		query_->bindValue(":target", target_name);
		query_->exec();
	}

	/// <summary> ��ȡ��ȥһ�ܵķ�����ɵ����. </summary>
	/// <returns> ��TodayData���ؽ��, ����ʱ��ֲ�,��target�ֲ�, label�ֲ�
	/// </returns>
	lon::tomato_clock::TodayData getTodayData() {
		using namespace lon::tomato_clock;
		TodayData data;
		// ��ȡ�����ÿ��Сʱ��ɵķ�������.
		query_->exec("SELECT hour, "
					 "count(hour)  "
					 "FROM ( "
					 "SELECT strftime('%H', FinishTime) AS hour "
					 "FROM finishedtomato "
					 "WHERE date('now', '-1 day') < date(FinishTime)  "
					 ") "
					 "GROUP BY hour "
					 "ORDER BY hour; ");

		while (query_->next()) {
			data.time_data_p[ query_->value(0).toInt() ] =
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
			data.total_time_p[ query_->value(0).toInt() ] =
				static_cast<uint16_t>(query_->value(1).toInt());
		}
		//��ȡ������ɵķ��ѵ�target���
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
			data.target_data.push_back(std::make_pair(
				query_->value(0).toString(), query_->value(1).toInt()));
		}
		//��ȡ������ɵķ��ѵ�label����
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
			data.label_data.push_back(std::make_pair(
				query_->value(0).toString(), query_->value(1).toInt()));
		}
		return data;
	}

	lon::tomato_clock::LastWeekData getLastWeekData() {
		using namespace lon::tomato_clock;
		LastWeekData data;
		// ��ȡ��ȥ�����ÿ����ɵķ�������.
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
			data.time_data_p[ query_->value(0).toInt() ] =
				static_cast<uint16_t>(query_->value(1).toInt());
		}

		// ��ȡ��ȥ����ÿ����ɵ���ʱ��
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
			data.total_time_p[ query_->value(0).toInt() ] =
				static_cast<uint16_t>(query_->value(1).toInt());
		}
		//��ȡ������ɵķ��ѵ�target���
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
			data.target_data.push_back(std::make_pair(
				query_->value(0).toString(), query_->value(1).toInt()));
		}
		//��ȡ������ɵķ��ѵ�label����
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
			data.label_data.push_back(std::make_pair(
				query_->value(0).toString(), query_->value(1).toInt()));
		}
		return data;
	}

	/// <summary> ��ȡ��ȥһ�µķ�����ɵ����. </summary>
	/// <returns> ��QString����洢��ɵķ��ѵ����ڵ��б�.��ʽΪYYYY-MM-DD
	/// </returns>
	lon::tomato_clock::LastMonthData getLastMonthData() {
		using namespace lon::tomato_clock;
		LastMonthData data;
		// ��ȡ���µ�ÿ����ɵķ�������.
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
			data.time_data_p[ query_->value(0).toInt() ] =
				static_cast<uint16_t>(query_->value(1).toInt());
		}

		// ��ȡ��ȥ����ÿ����ɵ���ʱ��
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
		// �˴�������ݿ��д��˳�����ǰʱ���ֵ, �ᵼ�³������ݷ��ʷ�Χ.
		while (query_->next()) {
			data.total_time_p[ query_->value(0).toInt() ] =
				static_cast<uint16_t>(query_->value(1).toInt());
		}

		//��ȡ������ɵķ��ѵ�target���
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
			data.target_data.push_back(std::make_pair(
				query_->value(0).toString(), query_->value(1).toInt()));
		}
		//��ȡ������ɵķ��ѵ�label����
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
			data.label_data.push_back(std::make_pair(
				query_->value(0).toString(), query_->value(1).toInt()));
		}
		return data;
	}

	// TODO make last year a bit different.
	/// <summary> ��ȡ��ȥһ��ķ�����ɵ����. </summary>
	/// <returns> ��QString����洢��ɵķ��ѵ����ڵ��б�.��ʽΪYYYY-MM-DD
	/// </returns>
	std::vector<QString> getLastYearData() {
		std::vector<QString> result;
		query_->exec("SELECT date(FinishTime) \
						FROM finishedtomato\
						WHERE date('now', '-1 year') < date(FinishTime);");
		while (query_->next()) {
			result.emplace_back(query_->value(0).toString());
		}
		return result;
	}


	std::vector<int> getWorkTimeLastMouth() { return std::vector<int>(); }

	std::vector<int> getWorkTimeLastYear() { return std::vector<int>(); }

	/// <summary> ��ĳʱ��εĹ���ʱ���Խ���ķ�ʽ���浽������. </summary>
	/// <param name: duration> ��durationΪ��λ����. eg: ��: 'month',
	/// ��:'day'</param>
	std::vector<int> getBestWorkTimeDesc(const QString &duration) {
		std::vector<int> result;
		query_->prepare("SELECT DuringTime,"
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

	QString getLabelByTarget() { return QString(); }

	// get targets by label name.
	/// <summary>
	/// get all targets belong to label.
	/// </summary>
	/// <param name="label">label����, ÿ����ǩΨһ, ��label��Ϊ��.</param>
	/// <returns>all targets' name.</returns>
	std::vector<QString> getTargetsByLabel(const QString &label) {
		std::vector<QString> result;
		if (label.isEmpty()) {
			query_->exec("SELECT TargetName FROM targets");
		} else {
			query_->exec("SELECT TargetName FROM targets WHERE LabelName =" +
						 label);
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
		query_->exec(
			"select LabelName, TargetName from targets order by LabelName");
		while (query_->next()) {
			result.push_back(std::make_pair(query_->value(0).toString(),
											query_->value(1).toString()));
		}
		return result;
	}

	bool targetExists(const QString &label, const QString &target) {
		query_->exec("select count(*) from targets where LabelName = " + label +
					 " and TargetName = " + target);
		return query_->value(0).toInt();
	}
};
} // namespace lon