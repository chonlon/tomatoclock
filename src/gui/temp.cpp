#include "temp.h"
#include "ui_temp.h"

temp::temp(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::temp) {
    ui->setupUi(this);
    f(1, 2);
}

temp::~temp() { delete ui; }


/**
 * \brief bbgrief
 * \param a aaa
 * \param b bbbb
 */
void temp::f(int a, int b) {
}