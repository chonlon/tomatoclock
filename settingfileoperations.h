#ifndef SETTINGFILEOPERATIONS_H
#define SETTINGFILEOPERATIONS_H
#include <QFile>

namespace lon {
    class ClockOptions;
}

class SettingFileOperations
{
public:
    SettingFileOperations();
    ~SettingFileOperations() {}

    void saveClockOptionToFile(const lon::ClockOptions& option);
    lon::ClockOptions readClockOptionFromFile();
private:
    QFile file_;
};

#endif // SETTINGFILEOPERATIONS_H
