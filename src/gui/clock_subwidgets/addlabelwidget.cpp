#include "addlabelwidget.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#pragma execution_character_set("utf-8")
#endif

lon::AddLabelWidget::AddLabelWidget(const std::list<QString> labels,
                                    QWidget* parent)
    : Widget(parent),
      labels_(labels) {
    line_edit_p_ = new QLineEdit(this);
    label_p_ = new QLabel(this);
    center_layout_p_ = new QHBoxLayout(this);

    label_p_->setText(QString{"标签名: "});
    label_p_->setFocus();
    line_edit_p_->setPlaceholderText(
        QString{"请输入标签名, 标签名不可重复."});
    center_layout_p_->addWidget(label_p_);
    center_layout_p_->addWidget(line_edit_p_);
    centerWidget()->setLayout(center_layout_p_);

    this->resize(QSize(400, 250));
    connect(this, SIGNAL(okButtonClicked()), this, SLOT(onOkButtonClicked()));
}

void lon::AddLabelWidget::labelExists() {
    showMessage(QString{"标签已存在, 请重新输入."});
}

void lon::AddLabelWidget::onOkButtonClicked() {
    QString input(line_edit_p_->text());
    auto iter = std::find(labels_.begin(), labels_.end(), input);
    if (iter != labels_.end())
        labelExists();
    else {
        emit labelAdded(input);
    }
}

void lon::AddLabelWidget::closeMessagebox() {
    if (messagebox_p_) {
        messagebox_p_->window()->close();
        delete messagebox_p_;
        messagebox_p_ = nullptr;
    }
    setLineEditFocus();
}

void lon::AddLabelWidget::setLineEditFocus() {
    line_edit_p_->setFocus(Qt::OtherFocusReason);
    line_edit_p_->selectAll();
}

void lon::AddLabelWidget::showMessage(const QString& message) {
    messagebox_p_ = new lon::MessageBox("", message);
    connect(messagebox_p_,
            SIGNAL(okButtonClicked()),
            this,
            SLOT(closeMessagebox()));
    connect(messagebox_p_,
            SIGNAL(cancelButtonClicked()),
            this,
            SLOT(closeMessagebox()));
    connect(messagebox_p_,
            SIGNAL(closeButtonClicked()),
            this,
            SLOT(setLineEditFocus()));
}
