#ifndef LISTWIDGET_HPP
#define LISTWIDGET_HPP

#include <memory>
#include <vector>

#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QWidget>

/// 这是一个简单的widget的list显示的封装.
namespace lon {
class ListWidget : public QWidget {
    Q_OBJECT
  private:
    QVBoxLayout *                         main_layout_;
    std::vector<std::shared_ptr<QWidget>> widget_list_;
    QWidget *                             widget;

    QScrollArea *scroll_area_p_;

  public:
    explicit ListWidget(QWidget *parent = nullptr)
        : QWidget(parent) {
        main_layout_ = new QVBoxLayout(this);
        widget       = new QWidget(this);
        main_layout_->setContentsMargins(5, 5, 5, 5);
        scroll_area_p_ = new QScrollArea(this);
        widget->setLayout(main_layout_);
        widget->resize(this->window()->size());
        scroll_area_p_->setWidget(widget);
    }

    void addWidget(QWidget *widget) {
        widget_list_.emplace_back(widget);
        main_layout_->addSpacing(20);
        main_layout_->addWidget(widget);
    }

    void resize(int w, int h) {
        QWidget::resize(w, h);
        scroll_area_p_->resize(w, h);
        widget->resize(w, h);
    }
};
} // namespace lon

#endif // LISTWIDGET_HPP