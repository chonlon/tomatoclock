#ifndef LABELSANDTARGETSWIDGET_H
#define LABELSANDTARGETSWIDGET_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>
#include <unordered_map>
#include <vector>

#include "../lon_widget/autodeletewidgetpointer.hpp"
#include "clock_database/DataStructure.hpp"

namespace lon {
class ListWidget;
class Button;
class ClockSql;
class AddLabelWidget;
class AddTargetWidget;

/*!
 * \class LabelsAndTargetsWidget
 *
 * \brief 显示所有Label以及显示Target主界面.
 *
 * \author LON
 */
class LabelsAndTargetsWidget : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* main_layout_p_;
    QHBoxLayout* labels_main_layout_p_;
    QVBoxLayout* add_label_button_layout_p_;
    QGridLayout* labels_layout_p_;
    QHBoxLayout* target_main_layout_p_;
    QVBoxLayout* target_button_layout_p_;

    QWidget* labels_widget_p_;
    ListWidget* targets_list_widget_p_;
    AutoDeleteWidgetPointer* current_widget_pointer_;

    QSpacerItem* label_widget_spacer_p_;
    QSpacerItem* target_button_spacer_p_;

    Button* add_label_button_p_;
    Button* add_target_button_p_;
    Button* history_button_p_;
    Button* setting_button_p_;
    Button* all_button_;

    AddLabelWidget* addlabelwidget_p_;
    AddTargetWidget* addtargetwidget_p_;

    ListWidget* all_targets_widget_p_;
    //开关数据库的开销大, 所以还是使用指针更好.
    ClockSql* sql_;

    std::unordered_map<Button*, AutoDeleteWidgetPointer*> button_map_;
    std::list<std::pair<QString, QString>>* labels_and_targets_p_;

    uint8_t current_cloumn;
    uint8_t current_row;

    std::shared_ptr<tomato_clock::LastWeekData> last_week_data_p_;
    std::shared_ptr<tomato_clock::LastMonthData> last_month_data_p_;

private:  // functions
    // default construction are not allowed.
    LabelsAndTargetsWidget();
    /// <summary>
    /// 将按钮添加到界面上显示
    /// </summary>
    /// <param name="button">需要添加的按钮指针.</param>
    /// <param name="text">添加的按钮的文本.</param>
    void addLabelButton(Button* button, const QString& text);

    /// <summary>
    /// 将Target添加到界面上显示, 将根据提供的labelname和targetname创建targetwidget.
    /// </summary>
    /// <param name="labelname">将要添加的taget所属的Label名字.</param>
    /// <param name="targetname">将要添加的target的名字.</param>
    /// <param name="index">此targetwidget添加的位置, -1为添加到末尾.</param>
    void addTargetWidget(QString labelname, QString targetname, int index = -1);

    void initConnect();

    /// <summary>
    /// 初始化所有的Label显示(显示于LabelLayout).
    /// </summary>
    void initLabelsLayout();

    /// <summary>
    /// 初始化特定labelname下的所有target显示.
    /// </summary>
    /// <param name="label_name">给定的labelname</param>
    /// <param name="getAllTargets">是否是显示所有target.</param>
    void initTargets(QString label_name, bool getAllTargets = false);

    /// <summary>
    /// 初始化TargetLayout的显示.
    /// </summary>
    void initTargetsLayout();

    // 将需要添加的label与target存到数据库中.
    void saveLabelToSql(const QString& label_name);
    void saveTargetToSql(const QString& label_name, const QString& target_name);

public:
    /// <summary>
    /// LabelsAndTargetsWidget的构造函数, 使用者需要提供ClockSql指针,
    /// 以满足数据要求
    /// </summary>
    /// <param name="sql">数据库指针, 使用者仍然保留*sql的所有权,
    /// 但此类可能会修改数据库.</param>
    explicit LabelsAndTargetsWidget(std::shared_ptr<tomato_clock::LastWeekData> week_data,
                                    std::shared_ptr<tomato_clock::LastMonthData> month_data,
                                    QWidget* parent = nullptr);

    void setLastWeekData(std::shared_ptr<tomato_clock::LastWeekData> ptr);
    void setLastMonthData(std::shared_ptr<tomato_clock::LastMonthData> ptr);

signals:
    void changeSetting();
    void showChart();
    void startClock(QString label_name, QString target_name);
    void redrawWidget();
public slots:
    /// <summary>
    /// 打开一个添加Label窗口.
    /// </summary>
    void addLabel();

    /// <summary>
    /// 打开一个添加Target窗口.
    /// </summary>
    void addTarget();

    /// <summary>
    /// 关闭添加Label窗口.
    /// </summary>
    void closeAddLabelWidget();

    /// <summary>
    /// 关闭添加Target窗口.
    /// </summary>
    void closeAddTargetWidget();

    /// <summary>
    /// label已成功添加, 将此lable存到数据库中, 更新窗口.
    /// </summary>
    /// <param name="text">label名</param>
    void labelAdded(QString text);

    /// <summary>
    /// 有一个label选择按钮被点击.
    /// </summary>
    void onLabelButtonClicked();

    /// <summary>
    /// target已成功添加, 将此target存到数据库中, 更新窗口.
    /// </summary>
    /// <param name="label">label名</param>
    /// <param name="target">target名</param>
    void targetAdded(QString label, QString target);

    /// <summary>
    /// 一个target已经完成, 将其从数据库中删除.
    /// </summary>
    void targetFinished(const QString& target_name);

    /// <summary>
    /// 删除标签.
    /// </summary>
    void deleteLabel();
    // void startClock(const QString &label_name, const QString &target_name);
};
}  // namespace lon
#endif  // LABELSANDTARGETSWIDGET_H
