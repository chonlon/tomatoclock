#ifndef ADDLABELWIDGET_H
#define ADDLABELWIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <list>

#include "lon_widget/messagebox.hpp"
#include "lon_widget/widget.hpp"
namespace lon {
class AddLabelWidget : public lon::Widget {
    Q_OBJECT
  private:
    QLineEdit *line_edit_p_;
	QLabel *label_p_;
	QHBoxLayout *center_layout_p_;

	std::list<QString> labels_;

  public:
    explicit AddLabelWidget(std::list<QString> labels, QWidget *parent = nullptr);

signals:
	void labelAdded(QString label_name);
private slots:
	void labelExists();
  public slots:
	void onOkButtonClicked();
	void onCancelButtonClicked();

    void showMessage(const QString &message);
};
} // namespace lon
#endif // ADDLABELWIDGET_H
