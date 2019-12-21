#ifndef LON_MESSAGEBOX
#define LON_MESSAGEBOX

#include "../lon_widget/widget.hpp"

#include <QMessageBox>

//////////////////////////////////////////////////////////////////////////
/// 如果想要实现点击某个按钮就自动把这个类释放的话, 只在此类中是无法做到的,
/// 目前想到两个方案, 1. 设置一个wrapper, 点击了按钮, 由wrapper释放内存,
/// 那么就算wrapper使用后没有释放,
/// 所用的内存也不过十几个字节(一个messagebox指针, 一个虚表指针).
/// 2. 对widget改写, 提供closewindow的信号, 使用者收到信号后delete.
/////////////////////////////////////////////////////////////////////////
namespace lon {
class MessageBox : public Widget {
Q_OBJECT
private:
    QLabel* text_label_p_;
    QBoxLayout* center_layout_p_;

public:
    MessageBox(QWidget* parent = nullptr)
        : Widget(parent) {
    }

    MessageBox(const QString& title,
               const QString& message,
               QWidget* parent = nullptr)
        : Widget(parent) {
        setTitle(title);

        text_label_p_ = new QLabel(this);
        text_label_p_->setText(message);

        center_layout_p_ = new QHBoxLayout(this);
        center_layout_p_->addStretch();
        center_layout_p_->addWidget(text_label_p_);
        center_layout_p_->addStretch();

        centerWidget()->setLayout(center_layout_p_);

        connect(this,
                SIGNAL(okButtonClicked()),
                this,
                SLOT(onOkButtonClicked()));
        connect(this,
                SIGNAL(cancelButtonClicked()),
                this,
                SLOT(onCancleButtonClicked()));
        this->show();
    }

private slots:
    void onOkButtonClicked() { window()->close(); }
    void onCancleButtonClicked() { window()->close(); }
};

class MessageBoxWrapper : QObject {
Q_OBJECT
private:
    // 不允许初始化在栈上.
    ~MessageBoxWrapper() = default;

protected:
    lon::MessageBox* message_box_p_;

    virtual void closeAndDelete() {
        message_box_p_->window()->close();
        delete message_box_p_;
        message_box_p_ = nullptr;
    }

public:
    MessageBoxWrapper(QString title, QString message, QObject* parent = nullptr)
        : QObject(parent) {
        message_box_p_ = new lon::MessageBox(title, message);
        connect(message_box_p_,
                SIGNAL(closeButtonClicked()),
                this,
                SLOT(onCloseButtonClicked()));
        connect(message_box_p_,
                SIGNAL(okButtonClicked()),
                this,
                SLOT(onOkButtonClicked()));
        connect(message_box_p_,
                SIGNAL(cancelButtonClicked()),
                this,
                SLOT(onCancelButtonClicked()));
    }

public slots:
    virtual void onCloseButtonClicked() { closeAndDelete(); }
    virtual void onOkButtonClicked() { closeAndDelete(); }
    virtual void onCancelButtonClicked() { closeAndDelete(); }
};
} // namespace lon
#endif
