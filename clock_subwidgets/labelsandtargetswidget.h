#ifndef LABELSANDTARGETSWIDGET_H
#define LABELSANDTARGETSWIDGET_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QString>
#include <QWidget>
#include <unordered_map>
#include <vector>

#include "clock_database/DataStructure.hpp"
#include "lon_widget/autodeletewidgetpointer.hpp"

namespace lon {
class ListWidget;
class Button;
class ClockSql;
class AddLabelWidget;
class AddTargetWidget;

/*!
 * \class LabelsAndTargetsWidget
 *
 * \brief ��ʾ����Label�Լ���ʾTarget������.
 *
 * \author LON
 */
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

    std::shared_ptr<lon::tomato_clock::LastWeekData>  last_week_data_p_;
    std::shared_ptr<lon::tomato_clock::LastMonthData> last_month_data_p_;

  private: // functions
    // default construction are not allowed.
    LabelsAndTargetsWidget();
	/// <summary>
	/// ����ť��ӵ���������ʾ
	/// </summary>
	/// <param name="button">��Ҫ��ӵİ�ťָ��.</param>
	/// <param name="text">��ӵİ�ť���ı�.</param>
    void addLabelButton(lon::Button *button, const QString &text);

	/// <summary>
	/// ��Target��ӵ���������ʾ, �������ṩ��labelname��targetname����targetwidget.
	/// </summary>
	/// <param name="labelname">��Ҫ��ӵ�taget������Label����.</param>
	/// <param name="targetname">��Ҫ��ӵ�target������.</param>
	/// <param name="index">��targetwidget��ӵ�λ��, -1Ϊ��ӵ�ĩβ.</param>
    void addTargetWidget(QString labelname, QString targetname, int index = -1);

    void initConnect();

	/// <summary>
	/// ��ʼ�����е�Label��ʾ(��ʾ��LabelLayout).
	/// </summary>
    void initLabelsLayout();

	/// <summary>
	/// ��ʼ���ض�labelname�µ�����target��ʾ.
	/// </summary>
	/// <param name="label_name">������labelname</param>
	/// <param name="getAllTargets">�Ƿ�����ʾ����target.</param>
    void initTargets(QString label_name, bool getAllTargets = false);

	/// <summary>
	/// ��ʼ��TargetLayout����ʾ.
	/// </summary>
    void initTargetsLayout();

	// ����Ҫ��ӵ�label��target�浽���ݿ���.
    void saveLabelToSql(const QString &label_name);
    void saveTargetToSql(const QString &label_name, const QString &target_name);

  public:
    /// <summary>
    /// LabelsAndTargetsWidget�Ĺ��캯��, ʹ������Ҫ�ṩClockSqlָ��,
    /// ����������Ҫ��
    /// </summary>
    /// <param name="sql">���ݿ�ָ��, ʹ������Ȼ����*sql������Ȩ,
    /// ��������ܻ��޸����ݿ�.</param>
    explicit LabelsAndTargetsWidget(
        std::shared_ptr<lon::tomato_clock::LastWeekData> week_data,
        std::shared_ptr<lon::tomato_clock::LastMonthData> month_data,
        QWidget *                                         parent = nullptr);

    void setLastWeekData(std::shared_ptr<lon::tomato_clock::LastWeekData> ptr);
    void
        setLastMonthData(std::shared_ptr<lon::tomato_clock::LastMonthData> ptr);

  signals:
    void changeSetting();
    void showChart();
    void startClock(QString label_name, QString target_name);
    void redrawWidget();
  public slots:
	  /// <summary>
	  /// ��һ�����Label����.
	  /// </summary>
    void addLabel();

	/// <summary>
	/// ��һ�����Target����.
	/// </summary>
    void addTarget();

	/// <summary>
	/// �ر����Label����.
	/// </summary>
    void closeAddLabelWidget();

	/// <summary>
	/// �ر����Target����.
	/// </summary>
    void closeAddTargetWidget();

	/// <summary>
	/// label�ѳɹ����, ����lable�浽���ݿ���, ���´���.
	/// </summary>
	/// <param name="text">label��</param>
    void labelAdded(QString text);

	/// <summary>
	/// ��һ��labelѡ��ť�����.
	/// </summary>
    void onLabelButtonClicked();

	/// <summary>
	/// target�ѳɹ����, ����target�浽���ݿ���, ���´���.
	/// </summary>
	/// <param name="label">label��</param>
	/// <param name="target">target��</param>
    void targetAdded(QString label, QString target);

	/// <summary>
	/// һ��target�Ѿ����, ��������ݿ���ɾ��.
	/// </summary>
	void targetFinished(const QString& target_name);

	/// <summary>
	/// ɾ����ǩ.
	/// </summary>
    void deleteLabel();
    // void startClock(const QString &label_name, const QString &target_name);
};
} // namespace lon
#endif // LABELSANDTARGETSWIDGET_H