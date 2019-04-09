#ifndef CUSTOMSLICEWITHVALUE_H
#define CUSTOMSLICEWITHVALUE_H

#include <QObject>
#include <QPieSlice>

class CustomSliceWithValue : public QPieSlice
{
    Q_OBJECT
private:
    QString name_;
public:
    CustomSliceWithValue(QObject *parent = nullptr);

    void setName(const QString& name);
    QString name() const;

public slots:

};

#endif // CUSTOMSLICEWITHVALUE_H
