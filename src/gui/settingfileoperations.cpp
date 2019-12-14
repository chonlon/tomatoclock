#include "settingfileoperations.h"
#include "clockoptions.hpp"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <fstream>

SettingFileOperations::SettingFileOperations() {
}

void SettingFileOperations::saveClockOptionToFile(
    const lon::ClockOptions& option) {
    QJsonObject clock_page;
    clock_page.insert("WorkTime", option.work_time()->minutes_);
    clock_page.insert("ShortbreakTime", option.sb_time()->minutes_);
    clock_page.insert("LongbreakTime", option.lb_time()->minutes_);
    clock_page.insert("TimesBetweenLong", option.sbtimes_between_lb());
    clock_page.insert("KeepWorking", static_cast<int8_t>(option.keepWorking()));
    QJsonObject json;
    json.insert("ClockSetting", QJsonValue(clock_page));
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Indented);

    // 这里用QFile 使用WriteOnly打开总是出错, 不知道原因, 暂时先用ofstream代替.
    std::string filename = "user/setting.json";
    std::ofstream setting_file(filename, std::ios::binary);
    setting_file.write(byteArray, byteArray.size());
    setting_file.close();
}

lon::ClockOptions SettingFileOperations::readClockOptionFromFile() {
    int8_t work = 25, shortbreak = 5, longbreak = 15, shortbreak_times = 3,
           keep_working = 0;
    QFile file_("user/setting.json");
    if (!file_.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "could not open file in " << __FILE__ << __LINE__;
        return lon::ClockOptions(work,
                                 0,
                                 shortbreak,
                                 0,
                                 longbreak,
                                 0,
                                 shortbreak_times,
                                 static_cast<bool>(keep_working));
    }
    QTextStream in(&file_);
    QString in_string = in.readAll();

    QJsonParseError error;
    QJsonDocument json_document =
        QJsonDocument::fromJson(in_string.toLatin1(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (!(json_document.isNull() || json_document.isEmpty()) &&
            json_document.isObject()) {
            QVariantMap data = json_document.toVariant().toMap();
            if (!data[QLatin1String("errorCode")].toInt()) {
                QVariantMap clock_settings;
                if (data.find(QLatin1String("ClockSetting")) != data.end())
                    clock_settings =
                        data[QLatin1String("ClockSetting")].toMap();
                if (clock_settings.find(QLatin1String("WorkTime")) !=
                    clock_settings.end())
                    work = clock_settings[QLatin1String("WorkTime")].toInt();
                if (clock_settings.find(QLatin1String("ShortbreakTime")) !=
                    clock_settings.end())
                    shortbreak =
                        clock_settings[QLatin1String("ShortbreakTime")]
                        .toInt();
                if (clock_settings.find(QLatin1String("LongbreakTime")) !=
                    clock_settings.end())
                    longbreak = clock_settings[QLatin1String("LongbreakTime")]
                        .toInt();
                if (clock_settings.find(QLatin1String("TimesBetweenLong")) !=
                    clock_settings.end())
                    shortbreak_times =
                        clock_settings[QLatin1String("TimesBetweenLong")]
                        .toInt();
                if (clock_settings.find(QLatin1String("KeepWorking")) !=
                    clock_settings.end())
                    keep_working =
                        clock_settings[QLatin1String("KeepWorking")].toInt();
            }
        }
    } else {
        qDebug() << "Error String : " << error.errorString();
    }
    file_.close();
    return lon::ClockOptions(work,
                             0,
                             shortbreak,
                             0,
                             longbreak,
                             0,
                             shortbreak_times,
                             static_cast<bool>(keep_working));
}
