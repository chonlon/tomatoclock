#ifndef SETTINGFILEOPERATIONS_H
#define SETTINGFILEOPERATIONS_H
#include <QFile>

namespace lon {
class ClockOptions;
}

class SettingFileOperations {
public:
    SettingFileOperations();

    ~SettingFileOperations() {
    }

    /**
     * \brief save clock options, invoke when setting changed and widget was closed.
     * \param option clock options operate by user.
     */
    void saveClockOptionToFile(const lon::ClockOptions& option);
    lon::ClockOptions readClockOptionFromFile();
};

#endif // SETTINGFILEOPERATIONS_H
