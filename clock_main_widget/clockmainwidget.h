#ifndef CLOCKMAINWIDGET_H
#define CLOCKMAINWIDGET_H

#include <QGridLayout>
#include <QVBoxLayout>
#include <QWidget>

#include "lon_widget/listwidget.hpp"
namespace lon {
/// <summary>
/// 这个类是番茄钟在主界面显示的总widget.
/// </summary>
class ClockMainWidget : public QWidget {
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
} // namespace lon

#endif // CLOCKMAINWIDGET_H
