#ifndef TARGETWIDGET_H
#define TARGETWIDGET_H

#include <QDebug>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "lon_widget/button.hpp"
namespace lon {
class TargetWidget : public QWidget {
    Q_OBJECT
  private:
    QLabel *     label_p_;
    QLabel *     target_label_p_;
    QGridLayout *main_layout_p_;

    lon::Button *start_target_button_p_;

    QString target_name_;
    QString label_name_;

  public:
    explicit TargetWidget(QString label_name, QString target_name,
                          QWidget *parent = nullptr);

  signals:
    void startButtonClicked(QString label, QString target);
  public slots:
    void emitButtonClicked() {
        emit startButtonClicked(label_name_, target_name_);
    }
};
} // namespace lon
#endif // TARGETWIDGET_H
