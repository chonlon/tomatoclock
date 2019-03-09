#ifndef TARGETSWIDGET_H
#define TARGETSWIDGET_H

#include <QGridLayout>
#include <QVBoxLayout>
#include <QWidget>

namespace lon {
class TargetsWidget : public QWidget {
    Q_OBJECT
  private:
    QGridLayout *labels_layout_p_;
    QVBoxLayout *targets_layout_p_;

  public:
    explicit TargetsWidget(QWidget *parent = nullptr);

  signals:

  public slots:
};
} // namespace lon
#endif // TARGETSWIDGET_H
