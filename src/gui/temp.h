#ifndef TEMP_H
#define TEMP_H

#include <QLabel>
#include <QWidget>
#include <QtCore>
#include <QtGui>

namespace Ui {
class temp;
}

class temp : public QWidget {
Q_OBJECT

public:
    explicit temp(QWidget* parent = nullptr);
    ~temp();

private:
    Ui::temp* ui;
    QLabel* label;
};

#endif // TEMP_H
