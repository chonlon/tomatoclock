#ifndef ADDTARGETWIDGET_H
#define ADDTARGETWIDGET_H

#include <QWidget>
#include <list>


#include "../lon_widget/widget.hpp"

class QComboBox;
class QLineEdit;
class QGridLayout;
class QLabel;

namespace lon {
	class ClockSql;
/*!
 * \class AddTargetWidget
 *
 * \brief 添加目标弹窗widget, 添加成功返回主界面, 更新显示, 添加失败弹出MessageBox提示.
 *
 * \author LON
 */
class AddTargetWidget : public lon::Widget {
	Q_OBJECT
  private:
	QComboBox *labels_combobox_p_;
	QLineEdit *lineedit_p_;
	QLabel *   select_label_p_;
	QLabel *   label_p_;

	QGridLayout *      main_layout_p_;
	std::list<QString> labels_;

	lon::ClockSql *sql_;

  public:
	explicit AddTargetWidget(std::list<QString> labels ,
							 QWidget *parent = nullptr);

signals:
	  /// <summary>
	  /// 当一个合法的target被添加, 则发射此信号.
	  /// </summary>
	void targetAdded(QString label_name, QString target_name);

  public slots:
	  /// <summary>
	  /// 按下Ok时, 检查输入是否合法, 合法则添加此target.
	  /// </summary>
	void onOkButtonClicked();

	/// <summary>
	/// 输入不合法时, 弹窗提示.
	/// </summary>
	void showMessage(const QString &message);
};
} // namespace lon

#endif // ADDTARGETWIDGET_H
