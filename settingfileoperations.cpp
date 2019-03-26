#include "settingfileoperations.h"
#include "clockoptions.hpp"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

SettingFileOperations::SettingFileOperations()
    : file_(":/all/user/setting.json") {}

void SettingFileOperations::saveClockOptionToFile(
    const lon::ClockOptions &option) {
    QJsonObject clock_page;
    clock_page.insert("WorkTime", option.work_time()->minutes_);
    clock_page.insert("ShortbreakTime", option.sb_time()->minutes_);
    clock_page.insert("LongbreakTime", option.lb_time()->minutes_);
	clock_page.insert("TimesBetweenLong", option.sbtimes_between_lb());
	QJsonObject json;
	json.insert("ClockSetting", QJsonValue(clock_page));
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Indented);

	if (!file_.open(QFile::WriteOnly)) {
        qDebug() << "could not open file in " << __FILE__ << __LINE__;
        return;
    }

	file_.write(byteArray);
	file_.close();
}

lon::ClockOptions SettingFileOperations::readClockOptionFromFile() {
    int8_t work = 25, shortbreak = 5, longbreak = 15, shortbreak_times = 3;
    if (!file_.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "could not open file in " << __FILE__ << __LINE__;
		return lon::ClockOptions(work, 0, shortbreak, 0, longbreak, 0, shortbreak_times);
    }
    QTextStream in(&file_);
    QString     in_string = in.readAll();

    QJsonParseError error;
    QJsonDocument   json_document =
        QJsonDocument::fromJson(in_string.toLatin1(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (!(json_document.isNull() || json_document.isEmpty()) &&
            json_document.isObject()) {
            QVariantMap data = json_document.toVariant().toMap();
            if (!data[ QLatin1String("errorCode") ].toInt()) {
                QVariantMap clock_settings;
                if (data.find(QLatin1String("ClockSetting")) != data.end())
                    clock_settings =
                        data[ QLatin1String("ClockSetting") ].toMap();
                if (clock_settings.find(QLatin1String("WorkTime")) !=
                    clock_settings.end())
                    work = clock_settings[ QLatin1String("WorkTime") ].toInt();
                if (clock_settings.find(QLatin1String("ShortbreakTime")) !=
                    clock_settings.end())
                    shortbreak =
                        clock_settings[ QLatin1String("ShortbreakTime") ]
                            .toInt();
                if (clock_settings.find(QLatin1String("LongbreakTime")) !=
                    clock_settings.end())
                    longbreak = clock_settings[ QLatin1String("LongbreakTime") ]
                                    .toInt();
                if (clock_settings.find(QLatin1String("TimesBetweenLong")) !=
                    clock_settings.end())
                    shortbreak_times =
                        clock_settings[ QLatin1String("TimesBetweenLong") ]
                            .toInt();
            }
        }
    } else {
        qDebug() << "Error String : " << error.errorString();
    }
	file_.close();
    return lon::ClockOptions(work, 0, shortbreak, 0, longbreak, 0, shortbreak_times);
}