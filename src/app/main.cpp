#include "../gui/clock_main_widget/clockmainwidget.h"
#include <QApplication>

/* TODO 1.圆角阴影
 * 2.点击特效
 * 3.完成弹窗以及声音
 * 4.弹出窗口的位置
 */


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    lon::ClockMainWidget c;
    c.show();

    return a.exec();
}
