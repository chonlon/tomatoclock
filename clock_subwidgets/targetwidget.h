#ifndef TARGETWIDGET_H
#define TARGETWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include "lon_widget/button.hpp"
namespace lon{

class TargetWidget : public QWidget
{
    Q_OBJECT
private:
	QLabel *label_p_;
	QLabel *target_label_p_;
	QGridLayout *main_layout_p_;

	lon::Button *start_target_button_p_;
public:
    explicit TargetWidget(QWidget *parent = nullptr);

signals:
	void startButtonClicked();
public slots:
};
}
#endif // TARGETWIDGET_H
