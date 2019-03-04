#ifndef TARGETSWIDGET_H
#define TARGETSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>

namespace lon {
class TargetsWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *labels_layout_p_;
    QVBoxLayout *targets_layout_p_;
public:
    explicit TargetsWidget(QWidget *parent = nullptr);

signals:

public slots:
};

}
#endif // TARGETSWIDGET_H
