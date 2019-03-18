#include "addlabelwidget.h"

lon::AddLabelWidget::AddLabelWidget(const std:: list<QString> labels, QWidget *parent)
    : lon::Widget(parent), labels_(labels) {
	line_edit_p_ = new QLineEdit(this);
	label_p_ = new QLabel(this);
	center_layout_p_ = new QHBoxLayout(this);

	label_p_->setText(tr("标签名: "));
	label_p_->setFocus();
	line_edit_p_->setPlaceholderText(tr("请输入标签名, 标签名不可重复."));
	center_layout_p_->addWidget(label_p_);
	center_layout_p_->addWidget(line_edit_p_);
	centerWidget()->setLayout(center_layout_p_);


	this->resize(QSize(400, 250));
	connect(this, SIGNAL(okButtonClicked()), this, SLOT(onOkButtonClicked()));
	connect(this, SIGNAL(cancelButtonClicked()), this, SLOT(onCancelButtonClicked()));
}

void lon::AddLabelWidget::labelExists()
{
	showMessage(QString::fromLocal8Bit("标签已存在, 请重新输入."));
}

void lon::AddLabelWidget::onOkButtonClicked()
{
	QString input(line_edit_p_->text());
	auto iter = std::find(labels_.begin(), labels_.end(), input);
	if (iter == labels_.end()) labelExists();
	emit labelAdded(input);
	this->window()->close();
}

void lon::AddLabelWidget::onCancelButtonClicked()
{
	this->window()->close();
}

void lon::AddLabelWidget::showMessage(const QString &message) {
    lon::MessageBox *mb = new lon::MessageBox("",message);
}
