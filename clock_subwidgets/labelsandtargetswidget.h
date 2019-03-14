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

#include "clock_database/clocksql.hpp"
#include "clock_subwidgets/targetwidget.h"
#include "lon_widget/autodeletewidgetpointer.hpp"
#include "lon_widget/button.hpp"
#include "lon_widget/listwidget.hpp"
namespace lon {
class LabelsAndTargetsWidget : public QWidget {
    Q_OBJECT
  private:
    QVBoxLayout *main_layout_p_;
    QHBoxLayout *labels_main_layout_p_;
    QVBoxLayout *add_label_button_layout_p_;
    QGridLayout *labels_layout_p_;
    QHBoxLayout *target_main_layout_p_;
    QVBoxLayout *target_button_layout_p_;

	QWidget *    labels_widget_p_;
    lon::ListWidget *targets_list_widget_p_;

	QSpacerItem *label_widget_spacer_p_;
    QSpacerItem *target_button_spacer_p_;

    lon::Button *add_label_button_p_;
    lon::Button *add_target_button_p_;
    lon::Button *history_button_p_;

    lon::ListWidget *all_targets_widget_p_;
    lon::ClockSql    sql_;

    std::unordered_map<lon::Button *, lon::AutoDeleteWidgetPointer*> button_map_;
private: // functions

  public:
    explicit LabelsAndTargetsWidget(QWidget *parent = nullptr);
	~LabelsAndTargetsWidget()
	{
		delete label_widget_spacer_p_;
	}

  signals:

  public slots:
    void onLabelButtonClicked();
};
} // namespace lon
#endif // LABELSANDTARGETSWIDGET_H