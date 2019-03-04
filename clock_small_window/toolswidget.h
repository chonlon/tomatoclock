#ifndef TOOLSWIDGET_H
#define TOOLSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "lon_widget/button.hpp"

namespace lon {
class ToolsWidget : public QWidget
{
    Q_OBJECT
private:
    QLabel *tomato_label_;
    QHBoxLayout *main_layout_;
    QVBoxLayout *window_operation_group_;

    lon::Button *close_;
    lon::Button *restore_;
    lon::Button *volume_;
    lon::Button *stop_;

private:

private slots:
    void onCloseClicked();
public:
    explicit ToolsWidget(QWidget *parent = nullptr);

signals:

public slots:
};

}
#endif // TOOLSWIDGET_H
