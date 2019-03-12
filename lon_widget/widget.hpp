#ifndef LON_WIDGET
#define LON_WIDGET

#include "button.hpp"
#include "titlebar.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtWidgets>
#include <QSizeGrip>
#include <cassert>

namespace lon {
/// 统一样式的widget订制.
/// 其实也只是一个简单的封装.
/// 如果某些地方不符合需要, 可以自定义窗口,
/// 但是务必使用lon::TitleBar以保持统一风格.
// 因为不是很确定bottom的界面具体情况, 如果是需要在默认的情况下绑定信号与槽的话
// 需要使用bottomBar()函数获得bottomBar的指针
/// <summary>
/// 统一样式的Widget.
/// 不允许自己定义layout(因为会破环titlebar),
/// 只允许对centerWidget和botttomWidget进行操作(包括替换).
///	</summary>
class Widget : public QWidget {
    Q_OBJECT
  private:
    lon::TitleBar *title_bar_;
    QWidget *      center_widget_;
    QWidget *      bottom_bar_;
	QSizeGrip	* size_grip_;

    lon::Button *ok_button_;
    lon::Button *cancel_button_;

    QGridLayout *p_layout_;

  private:
    // 禁用setlayout, 只允许操作centerWidget和botttomWidget.
    virtual void setLayout(QLayout *) {}

    void initLayout() {
        p_layout_ = new QGridLayout(this);
        p_layout_->setSpacing(0);
        p_layout_->addWidget(title_bar_, 0, 0);
        p_layout_->addWidget(center_widget_,1, 0);
        p_layout_->addWidget(bottom_bar_,2, 0);
        p_layout_->setContentsMargins(0, 0, 0, 0);

    }
    void initBottomBar() {
        bottom_bar_->setFixedHeight(50);
		bottom_bar_->setWindowFlags(Qt::SubWindow);

        QHBoxLayout *bottom_layout = new QHBoxLayout(bottom_bar_);

        ok_button_     = new lon::Button(bottom_bar_);
        cancel_button_ = new lon::Button(bottom_bar_);

        // 这里由于pushbutton不能使text在icon下面显示.
        // 所以只好使用样式表了
        // 或者这里得给ok_button换一个类型: QToolButton了.
        ok_button_->setStyleSheet(
            "QPushButton{border-image: url(:/icon/Resources/max_normal_normal.png);}\
               QPus0hButton:hover{border-image: url(:/icon/Resources/max_normal_focus.png);}\
               QPushButton:pressed{border-image: url(:/icon/Resources/max_normal_pressed.png);}");
        ok_button_->setText("确认");
        ok_button_->setFixedWidth(100);
        ok_button_->setFlat(true);

        cancel_button_->setStyleSheet(
            "QPushButton{border-image: url(:/icon/Resources/max_normal_normal.png);}\
               QPushButton:hover{border-image: url(:/icon/Resources/max_normal_focus.png);}\
               QPushButton:pressed{border-image: url(:/icon/Resources/max_normal_pressed.png);}");

        cancel_button_->setText("取消");
        cancel_button_->setFixedWidth(100);
        cancel_button_->setFlat(true);

		bottom_layout->addStretch();
        bottom_layout->addWidget(ok_button_);
		bottom_layout->addStretch();
        bottom_layout->addWidget(cancel_button_);
		bottom_layout->addStretch();

        bottom_bar_->setLayout(bottom_layout);
    }

    void initConnect() {
        connect(ok_button_, SIGNAL(clicked()), this, SLOT(onOkButtonClicked()));
        connect(cancel_button_, SIGNAL(clicked()), this,
                SLOT(onCancelButtonClicked()));
    }
protected:
	virtual void resizeEvent(QResizeEvent *event) {
		this->resize(event->size());
	}
  public:
    explicit Widget(QWidget *parent = nullptr)
        : QWidget(parent) {
        this->setWindowFlags(Qt::FramelessWindowHint |
                             Qt::WindowMinimizeButtonHint);
        title_bar_     = new lon::TitleBar(this);
        center_widget_ = new QWidget(this);
		bottom_bar_ = new QWidget(this);
		size_grip_ = new QSizeGrip(this);
		size_grip_->setFixedSize(size_grip_->sizeHint());

        initBottomBar();
        initLayout();
        initConnect();
		p_layout_->addWidget(size_grip_, 2, 1, Qt::AlignRight | Qt::AlignBottom);
    }

    explicit Widget(QWidget *center_widget, QWidget *bottom_bar,
                    QWidget *parent = nullptr)
        : QWidget(parent) {
        assert(center_widget && "pointer cannot be null");
        assert(bottom_bar && "pointer cannot be null");
        title_bar_ = new lon::TitleBar(this);

        center_widget_ = center_widget;
        bottom_bar_    = bottom_bar;

        initLayout();
        initConnect();
    }

    virtual ~Widget() {}

    /// <summary> 返回底部栏的widget指针. </summary>
    QWidget *bottomBar() const { return bottom_bar_; }
    /// <summary> 返回中间栏的widget指针. </summary>
    QWidget *centerWidget() const { return center_widget_; }

    /// <summary> 设置自定义的bottombar. </summary>
    /// 注意: 重新设置bottomBar会导致默认生成的按钮的信号与槽的失效.
    bool setBottomBar(QWidget *widget) {
        if (!widget) return false;

        p_layout_->removeWidget(bottom_bar_);

        delete bottom_bar_;

        bottom_bar_ = widget;
        p_layout_->addWidget(bottom_bar_,2, 0);
        return true;
    }

    /// <summary> 设置自定义的centerwidget. </summary>
    bool setCenterWidget(QWidget *widget) {
        if (!widget) return false;

        p_layout_->removeWidget(center_widget_);

        delete center_widget_;
        center_widget_ = widget;
		p_layout_->addWidget(center_widget_, 1, 0);
        return true;
    }

    virtual void setTitle(const QString &title) { title_bar_->setTitle(title); }

    virtual void setTitleIcon(const QIcon &icon) {
        title_bar_->setTitleIcon(icon);
    }

    virtual void setTitleBack(const QIcon &icon) {
        title_bar_->setBackground(icon);
    }

  signals:
    void okButtonClicked();
    void cancelButtonClicked();
  private slots:
    void onOkButtonClicked() { emit okButtonClicked(); }
    void onCancelButtonClicked() { emit cancelButtonClicked(); }
};
} // namespace lon

#endif