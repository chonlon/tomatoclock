#include "../gui/clock_main_widget/clockmainwidget.h"
#include "Translate/Translate.h"
#include <QApplication>
#include <QDialog>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    lon::ClockMainWidget c;
    c.show();

    Translate translate;

    return a.exec();
}
