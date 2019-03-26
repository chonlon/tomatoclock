#ifndef LON_MESSAGEBOX
#define LON_MESSAGEBOX

#include "lon_widget/widget.hpp"

#include <QMessageBox>
//////////////////////////////////////////////////////////////////////////
/// �����Ҫʵ�ֵ��ĳ����ť���Զ���������ͷŵĻ�, ֻ�ڴ��������޷�������,
/// Ŀǰ�뵽��������, 1. ����һ��wrapper, ����˰�ť, ��wrapper�ͷ��ڴ�,
/// ��ô����wrapperʹ�ú�û���ͷ�,
/// ���õ��ڴ�Ҳ����ʮ�����ֽ�(һ��messageboxָ��, һ�����ָ��).
/// 2. ��widget��д, �ṩclosewindow���ź�, ʹ�����յ��źź�delete.
/////////////////////////////////////////////////////////////////////////
namespace lon {
class MessageBox : public Widget {
    Q_OBJECT
  private:
    QLabel *    text_label_p_;
    QBoxLayout *center_layout_p_;

  public:
    MessageBox(QWidget *parent = nullptr)
        : Widget(parent) {}
    MessageBox(const QString &title, const QString &message,
               QWidget *parent = nullptr)
        : Widget(parent) {
        setTitle(title);

        text_label_p_ = new QLabel(this);
        text_label_p_->setText(message);

        center_layout_p_ = new QHBoxLayout(this);
        center_layout_p_->addStretch();
        center_layout_p_->addWidget(text_label_p_);
        center_layout_p_->addStretch();

        centerWidget()->setLayout(center_layout_p_);

        connect(this, SIGNAL(okButtonClicked()), this,
                SLOT(onOkButtonClicked()));
        connect(this, SIGNAL(cancelButtonClicked()), this,
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
    // �������ʼ����ջ��.
    ~MessageBoxWrapper() = default;

  protected:
    lon::MessageBox *message_box_p_;

    virtual void closeAndDelete() {
        message_box_p_->window()->close();
        delete message_box_p_;
        message_box_p_ = nullptr;
    }

  public:
    MessageBoxWrapper(QString title, QString message, QObject *parent = nullptr)
        : QObject(parent) {
        message_box_p_ = new lon::MessageBox(title, message);
        connect(message_box_p_, SIGNAL(closeButtonClicked()), this,
                SLOT(onCloseButtonClicked()));
        connect(message_box_p_, SIGNAL(okButtonClicked()), this,
                SLOT(onOkButtonClicked()));
        connect(message_box_p_, SIGNAL(cancelButtonClicked()), this,
                SLOT(onCancelButtonClicked()));
    }

  public slots:
    virtual void onCloseButtonClicked() { closeAndDelete(); }
    virtual void onOkButtonClicked() { closeAndDelete(); }
    virtual void onCancelButtonClicked() { closeAndDelete(); }
};
} // namespace lon
#endif