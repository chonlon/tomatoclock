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
 * \brief ���Ŀ�굯��widget, ��ӳɹ�����������, ������ʾ, ���ʧ�ܵ���MessageBox��ʾ.
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
	  /// ��һ���Ϸ���target�����, ������ź�.
	  /// </summary>
	void targetAdded(QString label_name, QString target_name);

  public slots:
	  /// <summary>
	  /// ����Okʱ, ��������Ƿ�Ϸ�, �Ϸ�����Ӵ�target.
	  /// </summary>
	void onOkButtonClicked();

	/// <summary>
	/// ���벻�Ϸ�ʱ, ������ʾ.
	/// </summary>
	void showMessage(const QString &message);
};
} // namespace lon

#endif // ADDTARGETWIDGET_H
