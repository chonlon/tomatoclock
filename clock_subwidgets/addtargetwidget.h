#ifndef ADDTARGETWIDGET_H
#define ADDTARGETWIDGET_H

#include <QWidget>
#include <list>

#include "lon_widget/widget.hpp"

class QComboBox;
class QLineEdit;
//class QHBoxLayout;
//class QVBoxLayout;
class QGridLayout;
class QLabel;

namespace lon{
class AddTargetWidget : public lon::Widget
{
    Q_OBJECT
private:
	QComboBox *labels_combobox_p_;
	QLineEdit *lineedit_p_;
	QLabel *select_label_p_;
	QLabel *label_p_;
	/*QHBoxLayout *input_layout_p_;
	QVBoxLayout *main_layout_p_;*/
	QGridLayout *main_layout_p_;
	std::list<QString> labels_;
	std::list<QString> targets_;
public:
    explicit AddTargetWidget(std::list<QString> labels, std::list<QString> targets, QWidget *parent = nullptr);

signals:
	void targetAdded(QString label_name, QString target_name);

public slots:
	void onOkButtonClicked();
	void onCancelButtonClicked();
};
}

#endif // ADDTARGETWIDGET_H
