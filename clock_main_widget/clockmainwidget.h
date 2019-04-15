#ifndef CLOCKMAINWIDGET_H
#define CLOCKMAINWIDGET_H

#include <QDateTime>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>

#include "clock_database/DataStructure.hpp"
#include "clock_database/clocksql.hpp"
#include "clockoptions.hpp"
#include "lon_widget/widget.hpp"

class QSystemTrayIcon;
class QGridLayout;
class QAction;
class QWidgetAction;

namespace lon {
class LabelsAndTargetsWidget;
class ClockRunningWidget;
class TomatoClockTimer;
class ClockSql;
class ChartsWidget;
class TitleBar;
class Menu;
namespace clock_window {
class ClockSmallWindow;
}
} // namespace lon
class SettingWidget;
namespace lon {
/// <summary>
/// 这个类是番茄钟在主界面显示的主界面.
/// </summary>
class ClockMainWidget : public lon::Widget {
    Q_OBJECT
  private:
    bool keep_working_;

    lon::LabelsAndTargetsWidget *labels_targets_widget_p_;
    lon::ClockRunningWidget *    clock_running_widget_p_;
    lon::ChartsWidget *          chart_widget_p_;
    lon::TitleBar *              title_bar_p_;

    SettingWidget *setting_widget_p_;

    lon::TomatoClockTimer *timer;

    QVBoxLayout *main_layout_;

    lon::ClockSql *sql_p_;

    QString running_clock_label_name_;
    QString running_clock_target_name_;

    std::shared_ptr<lon::tomato_clock::TodayData>     today_data_p_;
    std::shared_ptr<lon::tomato_clock::LastWeekData>  lastweek_data_p_;
    std::shared_ptr<lon::tomato_clock::LastMonthData> lastmonth_data_p_;

    QSystemTrayIcon *system_tray_icon_p_;

    lon::Menu *menu_p_;

    QAction *      close_action_p_;
    QAction *      about_action_p_;
    QAction *      setting_action_p_;
    QWidgetAction *clock_widget_action_p_;

  private:
    void tomatoSaveToSql();

  public:
    explicit ClockMainWidget(QWidget *parent = nullptr);

    virtual ~ClockMainWidget();
  signals:

  public slots:
    /// <summary>
    /// 切换显示计时状态.
    /// </summary>
    /// <param name="label">正在计时的番茄的Label属性.</param>
    /// <param name="target">正在计时的番茄的Target属性.</param>
    void displayClock(const QString &label, const QString &target);

    /// <summary>
    /// 切换显示主界面.
    /// </summary>
    void displayTarget();

    /// <summary>
    /// 切换显示图表.
    /// </summary>
    void displayChart();

    /// <summary>
    /// 一个番茄结束了, 存储番茄数据, 并根据用户设置决定是否返回主界面.
    /// </summary>
    void clockFinished();

    /// <summary>
    /// 有个番茄钟被提前结束了.
    /// </summary>
    void clockBreaked();

    /// <summary>
    /// 显示设置界面.
    /// </summary>
    void displaySetting();

    /// <summary>
    /// 将设置储存到设置文件中.
    /// </summary>
    /// <param name="option"></param>
    void saveSettingToFile(lon::ClockOptions option);

    /// <summary>
    /// 系统托盘响应动作.
    /// </summary>
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
};
} // namespace lon

#endif // CLOCKMAINWIDGET_H
