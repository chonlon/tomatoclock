#ifndef LISTWIDGET_HPP
#define LISTWIDGET_HPP

#include <memory>
#include <vector>

#include <QGraphicsEffect>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QWidget>
namespace lon {
/// 这是一个list显示widget的简单封装.
/// 这个类会获得添加的widget的所有权.
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
    virtual void setVerticalScrollBarStyle() {
        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
        // QWidget takes ownership of effect.
        scroll_area_p_->verticalScrollBar()->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(0.4);
        scroll_area_p_->verticalScrollBar()->setStyleSheet(
            "QScrollBar:vertical"
            "{"
            "border-radius:4px;"
            "background: white;"
            "width: 10px;"
            "margin: 0px 0px 0px 0px;"
            "}"
            "QScrollBar:vertical:hover"
            "{"
            "border-radius:4px;"
            "background: rgb(228,228,228);"
            "width: 10px;"
            "margin: 0px 0px 0 0px;"
            "}"
            "QScrollBar::handle:vertical "
            "{"
            "border-radius:3px;"
            "background: rgb(202,202,202);"
            "border-radius:4px;"
            "min-height: 20px;"
            "}"
            "QScrollBar::handle:vertical:hover"
            "{"
            "background: rgb(113,113,113);"
            "border-radius:4px;"
            "min-height: 20px;"
            "}"
            "QScrollBar::add-line:vertical "
            "{"
            "background: none;"
            "height: 10px;"
            "subcontrol-position: bottom;"
            "subcontrol-origin: margin;"
            "}"
            "QScrollBar::sub-line:vertical "
            "{"
            "background: none;"
            "height: 10px;"
            "subcontrol-position: top;"
            "subcontrol-origin: margin;"
            "}"
            "QScrollBar::up-arrow:vertical"
            "{"
            "}"
            "QScrollBar::up-arrow:vertical:hover"
            "{"
            "}"
            "QScrollBar::up-arrow:vertical:pressed"
            "{"
            "}"
            "QScrollBar::down-arrow:vertical "
            "{"
            "}"
            "QScrollBar::down-arrow:vertical:hover"
            "{"
            "}"
            "QScrollBar::down-arrow:vertical:pressed"
            "{"
            "}");
    }

  public:
    explicit ListWidget(QWidget *parent = nullptr)
        : QWidget(parent) {
        main_layout_ = new QVBoxLayout(this);
        widget_      = new QWidget();
        main_layout_->setContentsMargins(0, 0, 0, 0);
        scroll_area_p_ = new QScrollArea(this);
		scroll_area_p_->setFrameShape(QFrame::NoFrame);
        scroll_area_p_->setWidgetResizable(true);
        widget_->setLayout(main_layout_);
        widget_->resize(this->window()->size());
        // The widget becomes a child of the scroll area, and will be destroyed
        // when the scroll area is deleted or when a new widget is set.
        scroll_area_p_->setWidget(widget_);
        setVerticalScrollBarStyle();
    }

    void addWidget(QWidget *widget) {
        widget_list_.emplace_back(widget);
        main_layout_->addSpacing(20);
        main_layout_->addWidget(widget, Qt::AlignCenter);
    }

    void insertWidget(int index, QWidget *widget) {
        widget_list_.emplace_back(widget);
        main_layout_->addSpacing(20);
        main_layout_->insertWidget(index, widget, Qt::AlignCenter);
    }

    // void removeWidget(int index);

    std::shared_ptr<QWidget> indexOf(int index) {
        return widget_list_[ index ];
    }

    void resize(int w, int h) {
        QWidget::resize(w, h);
        scroll_area_p_->resize(w, h);
    }

    void setHorizontalScrollBarVisible(bool visible) {
        scroll_area_p_->horizontalScrollBar()->setVisible(visible);
        scroll_area_p_->setHorizontalScrollBarPolicy(
            Qt::ScrollBarPolicy::ScrollBarAsNeeded);
    }

    void setVerticalScrollBarVisible(bool visible) {
        scroll_area_p_->verticalScrollBar()->setVisible(visible);
        scroll_area_p_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }
};
} // namespace lon

#endif // LISTWIDGET_HPP