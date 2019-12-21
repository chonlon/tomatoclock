#ifndef LON_WIDGET
#define LON_WIDGET

#include "button.hpp"
#include "titlebar.hpp"
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QSizeGrip>
#include <QVBoxLayout>
#include <QtWidgets>
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
    TitleBar* title_bar_;

    QSizeGrip* size_grip_;

    Button* ok_button_;
    Button* cancel_button_;

    QGridLayout* p_layout_;

    bool size_girp_enabled;

    QPixmap* pixmap_;

    qint64 last_time_epoch_{0};
    // 这个属性主要是在设置了背景图以后每次resize的时候都会resize背景图,
    // 可以适当设置间隔一定的时间来提高resize的流畅度.
    qint64 reset_background_time_{50};

    QTimer timer_;
    bool block_one_;

protected:
    QWidget* center_widget_;
    QWidget* bottom_bar_;

private:
    // 禁用setlayout, 只允许操作centerWidget和botttomWidget.
    virtual void setLayout(QLayout*) {}

    void initLayout() {
        p_layout_ = new QGridLayout(this);
        p_layout_->setSpacing(0);
        p_layout_->addWidget(title_bar_, 0, 0, 1, 2);
        p_layout_->addWidget(center_widget_, 1, 0, 1, 2);
        p_layout_->addWidget(bottom_bar_, 2, 0, 1, 1);
        p_layout_->setContentsMargins(0, 0, 0, 0);
    }

    void initBottomBar() {
        bottom_bar_->setFixedHeight(50);
        bottom_bar_->setWindowFlags(Qt::SubWindow);

        QHBoxLayout* bottom_layout = new QHBoxLayout(bottom_bar_);

        ok_button_ = new Button(bottom_bar_);
        cancel_button_ = new Button(bottom_bar_);


        // 这里由于pushbutton不能使text在icon下面显示.
        // 所以只好使用样式表了
        // 或者这里得给ok_button换一个类型: QToolButton了.
        ok_button_->setStyleSheet(
            "QPushButton{border-image: url(:/icon/Resources/button.png);} "
            "QPus0hButton:hover{border-image: url(:/icon/Resources/button.png);} "
            "QPushButton:pressed{border-image: url(:/icon/Resources/button.png);} ");
        ok_button_->setText("确认");
        ok_button_->setFixedSize(90, 30);
        ok_button_->setFlat(true);

        cancel_button_->setStyleSheet(
            "QPushButton{border-image: url(:/icon/Resources/button.png);} "
            "QPus0hButton:hover{border-image: url(:/icon/Resources/button.png);} "
            "QPushButton:pressed{border-image: url(:/icon/Resources/button.png);} ");

        cancel_button_->setText("取消");
        cancel_button_->setFixedSize(90, 30);
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
        connect(cancel_button_, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
        connect(title_bar_, SIGNAL(minimizeButtonClicked()), this, SIGNAL(minimizeButtonClicked()));
        connect(title_bar_, SIGNAL(maximizeButtonClicked()), this, SIGNAL(maximizeButtonClicked()));
        connect(title_bar_, SIGNAL(closeButtonClicked()), this, SIGNAL(closeButtonClicked()));
        connect(&timer_, &QTimer::timeout, [this]() {
            this->setBackground(pixmap_);
            block_one_ = false;
        });
    }

    void initWidgets() {
        pixmap_ = nullptr;
        timer_.setSingleShot(true);
        QPalette palette;
        palette.setBrush(this->backgroundRole(), QBrush(QColor(255, 255, 255, 30)));
        title_bar_->setPalette(palette);
    }

protected:
    void resizeEvent(QResizeEvent* event) override {
        QWidget::resizeEvent(event);
        sizeChanged(event);
        if (pixmap_ == nullptr)
            return;
        if (pixmap_->isNull())
            return;
        const auto current_epoch = QDateTime::currentMSecsSinceEpoch();
        // qDebug() << event->size().width() << " h: " << event->size().height() << "\n";
        // this->setBackground(pixmap_);
        if (last_time_epoch_ == 0) {
            this->setBackground(pixmap_);
        } else if (current_epoch - last_time_epoch_ >= reset_background_time_) {
            this->setBackground(pixmap_);
            qDebug() << current_epoch << "direct";
        } else {
            if (!block_one_) {
                timer_.start(reset_background_time_);
                block_one_ = true;
            } else {
                timer_.stop();
                this->setBackground(pixmap_);
                block_one_ = false;
            }
        }
        last_time_epoch_ = current_epoch;
    }

public:
    explicit Widget(QWidget* parent = nullptr, TitleBar::Buttons status = TitleBar::ALL)
        : QWidget(parent) {
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
        title_bar_ = new TitleBar(this, status);
        center_widget_ = new QWidget();
        bottom_bar_ = new QWidget();
        size_girp_enabled = false;

        initWidgets();
        initBottomBar();
        initLayout();
        initConnect();
    }

    explicit Widget(QWidget* center_widget, QWidget* bottom_bar, QWidget* parent = nullptr)
        : QWidget(parent) {
        assert(center_widget && "pointer cannot be null");
        assert(bottom_bar && "pointer cannot be null");
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

        title_bar_ = new TitleBar(this);

        center_widget_ = center_widget;
        bottom_bar_ = bottom_bar;

        initWidgets();
        initLayout();
        initConnect();
    }

    virtual ~Widget() {
        delete pixmap_;
        delete center_widget_;
        delete bottom_bar_;
    }

    qint64 getResetBackgroundTime() const {
        return reset_background_time_;
    }

    void setResetBackgroundTime(const qint64 reset_background_time) {
        reset_background_time_ = reset_background_time;
    }

    /// <summary> 返回中间栏的widget指针. </summary>
    QWidget* centerWidget() const {
        return center_widget_;
    }

    /// <summary> 设置自定义的bottombar. </summary>
    /// 注意: 重新设置bottomBar会导致默认生成的按钮的信号与槽的失效.
    /// 此类会获取次widget的所有权.
    virtual bool setBottomBar(QWidget* widget) {
        p_layout_->removeWidget(bottom_bar_);

        delete bottom_bar_;

        bottom_bar_ = widget;
        if (bottom_bar_)
            p_layout_->addWidget(bottom_bar_, 2, 0, 1, 1);
        return true;
    }

    /// <summary> 设置自定义的centerwidget. </summary>
    /// 此类会获得widget的所有权.
    virtual bool setCenterWidget(QWidget* widget) {
        if (!widget)
            return false;

        p_layout_->removeWidget(center_widget_);

        delete center_widget_;
        center_widget_ = widget;

        if (center_widget_)
            p_layout_->addWidget(center_widget_, 1, 0);
        return true;
    }

    /// <summary> 返回底部栏的widget指针. </summary>
    QWidget* bottomBar() const {
        return bottom_bar_;
    }
    virtual void setTitle(const QString& title) {
        title_bar_->setTitle(title);
    }

    virtual void setTitleIcon(const QIcon& icon) {
        title_bar_->setTitleIcon(icon);
    }

    // this class will take pixmap's ownship

    virtual void setTitleBackground(QPixmap* pixmap) {
        title_bar_->setBackground(pixmap);
    }

    virtual void enabelSizeGrip() {
        size_girp_enabled = true;
        size_grip_ = new QSizeGrip(this);
        size_grip_->setFixedSize(size_grip_->sizeHint());
        p_layout_->addWidget(size_grip_, 2, 1, Qt::AlignRight | Qt::AlignBottom);
    }

    virtual bool sizeGripEnabled() {
        return size_girp_enabled;
    }

    // this class will take pixmap's ownship
    virtual void setBackground(QPixmap* pixmap) {
        this->setAutoFillBackground(true);
        //判断图片是否为空
        if (pixmap->isNull()) {
            qDebug() << tr("illege arguments, your image is empty") << __FILE__ << "\n";
            return;
        }
        //设置窗口的背景
        QPalette palette = this->palette();
        auto brush =
            QBrush(pixmap->scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        palette.setBrush(this->backgroundRole(), std::move(brush));
        this->setPalette(palette);
        pixmap_ = pixmap;
    }

    /// <summary>
    /// 设置最小化按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    virtual void setMinFunc(std::function<void(void)> val) {
        title_bar_->setMinFunc(val);
    }

    /// <summary>
    /// 设置最大化按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    virtual void setMaxFunc(std::function<void(void)> val) {
        title_bar_->setMaxFunc(val);
    }

    /// <summary>
    /// 关闭按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    virtual void setCloseFunc(std::function<void(void)> val) {
        title_bar_->setCloseFunc(val);
    }

signals:
    void okButtonClicked();
    void cancelButtonClicked();
    void minimizeButtonClicked();
    void maximizeButtonClicked();
    void closeButtonClicked();
    void sizeChanged(QResizeEvent* event);
private slots:
    void onOkButtonClicked() {
        emit okButtonClicked();
    }

    void onCancelButtonClicked() {
        emit cancelButtonClicked();
    }
};

class ShadowWindow : public QWidget {
    Q_OBJECT
public:
    explicit ShadowWindow(QWidget* contentWidget, QWidget* parent = nullptr) : QWidget(parent) {
        setWindowFlags(Qt::FramelessWindowHint);     // 去掉边框
        setAttribute(Qt::WA_TranslucentBackground);  // 背景透明

        // 添加阴影
        QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(contentWidget);
        shadowEffect->setColor(Qt::lightGray);
        shadowEffect->setBlurRadius(6);  // 阴影的大小
        shadowEffect->setOffset(0, 0);
        contentWidget->setGraphicsEffect(shadowEffect);

        // 添加到窗口中
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(contentWidget);
        layout->setContentsMargins(4, 4, 4, 4);  // 注意和阴影大小的协调
        setLayout(layout);
        connect(contentWidget,
                SIGNAL(sizeChanged(QResizeEvent*)),
                this,
                SLOT(sizeChanged(QResizeEvent*)));
    }

public slots:
    void sizeChanged(QResizeEvent* event) {
        this->resize(event->size().width() + 8, event->size().height() + 8);
    }
};
}  // namespace lon

#endif
