#ifndef LABELSANDTARGETSWIDGET_H
#define LABELSANDTARGETSWIDGET_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>
#include <unordered_map>
#include <vector>

#include "lon_widget/autodeletewidgetpointer.hpp"

namespace lon {
class ListWidget;
class Button;
class ClockSql;
class AddLabelWidget;
class AddTargetWidget;

class LabelsAndTargetsWidget : public QWidget {
    Q_OBJECT
  private:
    QVBoxLayout *main_layout_p_;
    QHBoxLayout *labels_main_layout_p_;
    QVBoxLayout *add_label_button_layout_p_;
    QGridLayout *labels_layout_p_;
    QHBoxLayout *target_main_layout_p_;
    QVBoxLayout *target_button_layout_p_;

    QWidget *                     labels_widget_p_;
    lon::ListWidget *             targets_list_widget_p_;
    lon::AutoDeleteWidgetPointer *current_widget_pointer_;

    QSpacerItem *label_widget_spacer_p_;
    QSpacerItem *target_button_spacer_p_;

    Button *add_label_button_p_;
    Button *add_target_button_p_;
    Button *history_button_p_;
    Button *setting_button_p_;
    Button *all_button_;

    lon::AddLabelWidget * addlabelwidget_p_;
    lon::AddTargetWidget *addtargetwidget_p_;

    ListWidget *all_targets_widget_p_;
    //�������ݿ�Ŀ�����, ���Ի���ʹ��ָ�����.
    ClockSql *sql_;

    std::unordered_map<lon::Button *, lon::AutoDeleteWidgetPointer *>
                                            button_map_;
    std::list<std::pair<QString, QString>> *labels_and_targets_p_;

    uint8_t current_cloumn;
    uint8_t current_row;

  private: // functions
    // default construction are not allowed.
    LabelsAndTargetsWidget();

    void addLabelButton(lon::Button *button, const QString &text);
    void addTargetWidget(QString labelname, QString targetname, int index = -1);
    void initConnect();
    void initLabelsLayout();
    void initTargets(QString label_name, bool getAllTargets = false);
    void initTargetsLayout();
    void saveLabelToSql(const QString &label_name);
    void saveTargetToSql(const QString &label_name, const QString &target_name);


  public:
    /// <summary>
    /// LabelsAndTargetsWidget�Ĺ��캯��, ʹ������Ҫ�ṩClockSqlָ��,
    /// ����������Ҫ��
    /// </summary>
    /// <param name="sql">���ݿ�ָ��, ʹ������Ȼ����*sql������Ȩ,
    /// ��������ܻ��޸����ݿ�.</param>
    explicit LabelsAndTargetsWidget(lon::ClockSql *sql,
                                    QWidget *      parent = nullptr);

  signals:
    void changeSetting();
    void showChart();
    void startClock(QString label_name, QString target_name);
    void redrawWidget();
  public slots:
    void addLabel();
    void addTarget();
    void closeAddLabelWidget();
    void closeAddTargetWidget();
    void labelAdded(QString text);
    void onLabelButtonClicked();
    void targetAdded(QString label, QString target);
	void deleteLabel();
    // void startClock(const QString &label_name, const QString &target_name);
};
} // namespace lon
#endif // LABELSANDTARGETSWIDGET_H