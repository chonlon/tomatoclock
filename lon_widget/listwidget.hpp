#ifndef LISTWIDGET_HPP
#define LISTWIDGET_HPP

#include <memory>
#include <vector>

#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QResizeEvent>

namespace lon {
/// 这是一个list显示widget的简单封装.
class ListWidget : public QWidget {
    Q_OBJECT
  private:
    QVBoxLayout *                         main_layout_;
    std::vector<std::shared_ptr<QWidget>> widget_list_;
    QWidget *                             widget_;

    QScrollArea *scroll_area_p_;

  protected:
	  virtual void resizeEvent(QResizeEvent *event) {
		  int w = event->size().width();
		  int h = event->size().height();
		  this->resize(w, h);
	  }

  public:
    explicit ListWidget(QWidget *parent = nullptr)
        : QWidget(parent) {
        main_layout_ = new QVBoxLayout(this);
        widget_      = new QWidget();
        main_layout_->setContentsMargins(0, 0, 0, 0);
        scroll_area_p_ = new QScrollArea(this);
		scroll_area_p_->setWidgetResizable(true);
        widget_->setLayout(main_layout_);
        widget_->resize(this->window()->size());
        scroll_area_p_->setWidget(widget_);
    }

    void addWidget(QWidget *widget) {
        widget_list_.emplace_back(widget);
        main_layout_->addSpacing(20);
        main_layout_->addWidget(widget);
    }

    void resize(int w, int h) {
		QWidget::resize(w, h);
        scroll_area_p_->resize(w, h);
    }

	void setHorizontalScrollBarVisible(bool visible) {
        scroll_area_p_->horizontalScrollBar()->setVisible(visible);
	}

	void setVerticalScrollBarVisible(bool visible) {
        scroll_area_p_->verticalScrollBar()->setVisible(visible);
	}
};
} // namespace lon

#endif // LISTWIDGET_HPP
