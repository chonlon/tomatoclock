#ifndef TOMATOCLOCKTIMER_H
#define TOMATOCLOCKTIMER_H

#include <QObject>

class TomatoClockTimer : public QObject
{
    Q_OBJECT
public:
    explicit TomatoClockTimer(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TOMATOCLOCKTIMER_H