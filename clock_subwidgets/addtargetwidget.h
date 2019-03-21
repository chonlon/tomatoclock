#ifndef ADDTARGETWIDGET_H
#define ADDTARGETWIDGET_H

#include <QWidget>
#include <list>

#include "clock_database/clocksql.hpp"
#include "lon_widget/widget.hpp"

class QComboBox;
class QLineEdit;
// class QHBoxLayout;
// class QVBoxLayout;
class QGridLayout;
class QLabel;

namespace lon {
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
    explicit AddTargetWidget(std::list<QString> labels, lon::ClockSql *sql,
                             QWidget *parent = nullptr);

  signals:
    void targetAdded(QString label_name, QString target_name);

  public slots:
    void onOkButtonClicked();

    void showMessage(const QString &message);
};
} // namespace lon

#endif // ADDTARGETWIDGET_H
