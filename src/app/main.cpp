#include "../gui/clock_main_widget/clockmainwidget.h"
#include <QApplication>
#include <QDialog>
#include "../gui/mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    lon::ClockMainWidget c;
    c.show();

    return a.exec();
}
