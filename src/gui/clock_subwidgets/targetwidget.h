#ifndef TARGETWIDGET_H
#define TARGETWIDGET_H

#include <QDebug>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "../lon_widget/button.hpp"
#include "clock_database/DataStructure.hpp"

namespace lon {
class ClockSql;

class TargetWidget : public QWidget {
    Q_OBJECT
private:
    void initWidgets();
    void setWidgetsStyle();
    void setThisWidgetStyle();
    /*
     *  The layout of this widget looks like this.
        +------------------------------------------------------------+
        | +------+ +---------+  +-----------+ +----------+  +------+ |
        | |spacer| |label    |  |week       | |month     |  |play  | |
        | +------+ +---------+  +-----------+ +----------+  |button| |
        | +------+ +---------+  +-----------+ +----------+  |      | |
        | |spacer| |target   |  |week reminder|month     |  |      | |
        | +------+ +---------+  +-----------+ +----------+  +------+ |
        +------------------------------------------------------------+
     */
    void initLayout();

    void drawWorkStuation(QWidget* widget, int num);

private:
    QLabel* label_p_;
    QLabel* target_label_p_;
    QLabel* week_label_p_;
    QLabel* month_label_p_;
    QLabel* week_situation_widget_p_;
    QLabel* month_situation_widget_p_;

    QGridLayout* main_layout_p_;

    Button* start_target_button_p_;
    Button* complete_target_button_p_;

    QString target_name_;
    QString label_name_;

    std::shared_ptr<tomato_clock::LastWeekData> last_week_data_p_;
    std::shared_ptr<tomato_clock::LastMonthData> last_month_data_p_;

public:
    explicit TargetWidget(QString label_name, QString target_name, QWidget* parent = nullptr);
    void setLastWeekData(std::shared_ptr<tomato_clock::LastWeekData> ptr);
    void setLastMonthData(std::shared_ptr<tomato_clock::LastMonthData> ptr);
signals:
    void startButtonClicked(QString label, QString target);
    void targetFinished(const QString& target_name);
public slots:
    void emitButtonClicked() {
        emit startButtonClicked(label_name_, target_name_);
    }
};
}  // namespace lon
#endif  // TARGETWIDGET_H
