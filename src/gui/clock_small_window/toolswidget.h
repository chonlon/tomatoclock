#ifndef TOOLSWIDGET_H
#define TOOLSWIDGET_H

#include <QWidget>

class QLabel;
class QGridLayout;

namespace lon {
class Button;

class ToolsWidget : public QWidget {
Q_OBJECT
private:
    QGridLayout* main_layout_;

    QLabel* label_label_;
    QLabel* target_label_;

    Button* close_;
    Button* stop_;

private:
private slots:
    void onCloseClicked();

public:
    explicit ToolsWidget(const QString& label_name,
                         const QString& target_name,
                         QWidget* parent = nullptr);

signals:
    void stopButtonClicked();
    void closeButtonClicked();
public slots:
};
} // namespace lon
#endif // TOOLSWIDGET_H
