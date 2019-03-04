#ifndef CLOCKMAINWIDGET_H
#define CLOCKMAINWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>

#include "lon_widget/listwidget.hpp"
namespace lon {

class ClockMainWidget : public QWidget
{
    Q_OBJECT
private:
    lon::ListWidget *list_widget_p_;

    QGridLayout *top_layout_p_;
    QVBoxLayout *main_layout_p_;

public:
    explicit ClockMainWidget(QWidget *parent = nullptr);



signals:

public slots:
    // 是否切换显示计时
    void switchToDisplayClock() {}
    void switchToDispalyTarget() {}
};

}

#endif // CLOCKMAINWIDGET_H
