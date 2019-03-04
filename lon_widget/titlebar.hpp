#ifndef LON_TITLEBAR
#define LON_TITLEBAR

#include "button.hpp"
#include <QApplication>
#include <QEvent>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QMouseEvent>
#include <QWidget>
#include <cassert>
#include <memory>

namespace lon {
static const int32_t BUTTON_HEIGHT    = 30;
static const int32_t BUTTON_WIDTH     = 45;
static const int32_t TITLE_BAR_HEIGHT = 50;

class TitleBar : public QWidget {
    Q_OBJECT
  private:
    QLabel *icon_label_;
    QLabel *title_label_;

    lon::Button *pminimize_button_;
    lon::Button *pmaximize_button_;
    lon::Button *pclose_button_;

    std::shared_ptr<QIcon> max_max_normal_;
    std::shared_ptr<QIcon> max_max_focus_;
    std::shared_ptr<QIcon> max_max_pressed_;

    std::shared_ptr<QIcon> max_normal_normal_;
    std::shared_ptr<QIcon> max_normal_focus_;
    std::shared_ptr<QIcon> max_normal_pressed_;

    QHBoxLayout *title_bar_layout_;

    bool   is_pressed_;
    QPoint move_start_position_;

  private:
    // 点击最大化按钮以后需要更新一些控件
    void updateMaximize() {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel()) {
            bool bMaximize = pWindow->isMaximized();
            if (bMaximize) {
                pmaximize_button_->setToolTip(tr("还原"));
                pmaximize_button_->setProperty("maximizeProperty", "restore");

                pmaximize_button_->setNormal(max_max_normal_);
                pmaximize_button_->setFocus(max_max_focus_);
                pmaximize_button_->setPressed(max_max_pressed_);
            } else {
                pmaximize_button_->setProperty("maximizeProperty", "maximize");
                pmaximize_button_->setToolTip(tr("最大化"));

                pmaximize_button_->setNormal(max_normal_normal_);
                pmaximize_button_->setFocus(max_normal_focus_);
                pmaximize_button_->setPressed(max_normal_pressed_);
            }
            // this->resize()
            pmaximize_button_->setStyle(QApplication::style());
        }
    }
    void initWidgets(int32_t button) {
        const char minn = 4;
        const char maxn = 2;

        //初始化最小化按钮
        if ((button & minn) == minn) {
            pminimize_button_ = new lon::Button(
                new QIcon(":/icon/Resources/min_normal.png"),  // normal
                new QIcon(":/icon/Resources/min_focus.png"),   // focus
                new QIcon(":/icon/Resources/min_pressed.png"), // pressed
                this);
            pminimize_button_->setFlat(true);
            pminimize_button_->setStyleSheet("border:none");
            pminimize_button_->setFixedSize(BUTTON_WIDTH, BUTTON_WIDTH);
            pminimize_button_->setObjectName("minimizeButton");
            pminimize_button_->setToolTip("最小化");
        }

        //初始化最大化按钮
        if ((button & maxn) == maxn) {
            pmaximize_button_ = new lon::Button(this);

            pmaximize_button_->setNormal(max_normal_normal_);
            pmaximize_button_->setFocus(max_normal_focus_);
            pmaximize_button_->setPressed(max_normal_pressed_);
            pmaximize_button_->setFlat(true);
            pmaximize_button_->setStyleSheet("border:none");
            pmaximize_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
            pmaximize_button_->setObjectName("maximizeButton");
            pmaximize_button_->setToolTip("最大化");
        }
        // 初始化关闭按钮
        pclose_button_ = new lon::Button(
            new QIcon(":/icon/Resources/close_normal.png"),  // normal
            new QIcon(":/icon/Resources/close_focus.png"),   // focus
            new QIcon(":/icon/Resources/close_pressed.png"), // pressedthis
            this);
        pclose_button_->setFlat(true);
        pclose_button_->setStyleSheet("border:none");
        pclose_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
        pclose_button_->setObjectName("closeButton");
        pclose_button_->setToolTip("关闭窗口");

        // 初始化两个label
        icon_label_ = new QLabel(this);
        icon_label_->setFixedSize(30, 30);
        icon_label_->setScaledContents(true);

        title_label_ = new QLabel(this);
        title_label_->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Expanding);
        title_label_->setObjectName("titleLable");
    }
    void initLayout(int32_t button) {
        const char minn   = 4;
        const char maxn   = 2;
        title_bar_layout_ = new QHBoxLayout(this);
        title_bar_layout_->addWidget(icon_label_);
        title_bar_layout_->addSpacing(5);
        title_bar_layout_->addWidget(title_label_);
        title_bar_layout_->setSpacing(0);

        if ((button & minn) == minn)
            title_bar_layout_->addWidget(pminimize_button_);
        if ((button & maxn) == maxn)
            title_bar_layout_->addWidget(pmaximize_button_);
        title_bar_layout_->addWidget(pclose_button_);

        title_bar_layout_->setContentsMargins(5, 0, 0, 0);

        this->setLayout(title_bar_layout_);
    }
    void initConnection(int32_t button) {
        const char minn = 4;
        const char maxn = 2;

        if ((button & minn) == minn)
            connect(pminimize_button_, SIGNAL(clicked(bool)), this,
                    SLOT(onButtonClicked()));
        if ((button & maxn) == maxn)
            connect(pmaximize_button_, SIGNAL(clicked(bool)), this,
                    SLOT(onButtonClicked()));
        connect(pclose_button_, SIGNAL(clicked(bool)), this,
                SLOT(onButtonClicked()));
    }

    void initMaxIcons(int32_t button) {
        const char maxn = 2;
        if ((button & maxn) != maxn) return;

        max_max_normal_.reset(new QIcon(":/icon/Resources/max_max_normal.png"));
        max_max_focus_.reset(new QIcon(":/icon/Resources/max_max_focus.png"));
        max_max_pressed_.reset(
            new QIcon(":/icon/Resources/max_max_pressed.png"));

        max_normal_normal_.reset(
            new QIcon(":/icon/Resources/max_normal_normal.png"));
        max_normal_focus_.reset(
            new QIcon(":/icon/Resources/max_normal_focus.png"));
        max_normal_pressed_.reset(
            new QIcon(":/icon/Resources/max_normal_pressed.png"));
    }

  protected:
    /// 双击标题栏进行界面的最大化/还原
    virtual void mouseDoubleClickEvent(QMouseEvent *event) {
        Q_UNUSED(event);
        emit pmaximize_button_->clicked();
    }

    // 按住titlebar会进行窗口的拖放
    // 事实上是使用下面三个函数(press, move, release)计算按下时移动距离
    // 在press的时候进行计算
    // 并在release的时候结束计算
    virtual void mousePressEvent(QMouseEvent *event) {
        if (this->window()->isMaximized()) return;

        is_pressed_          = true;
        move_start_position_ = event->globalPos();
        return QWidget::mousePressEvent(event);
    }
    virtual void mouseMoveEvent(QMouseEvent *event) {
        if (!is_pressed_) return;

        QPoint move_point = event->globalPos() - move_start_position_;
        QPoint widget_pos = this->window()->pos();

        move_start_position_ = event->globalPos();
        this->window()->move(widget_pos.x() + move_point.x(),
                             widget_pos.y() + move_point.y());
        return QWidget::mouseMoveEvent(event);
    }
    virtual void mouseReleaseEvent(QMouseEvent *event) {
        is_pressed_ = false;
        return QWidget::mouseReleaseEvent(event);
    }

    /// 设置默认界面标题与图标
    virtual bool eventFilter(QObject *obj, QEvent *event) {
        switch (event->type()) {
        case QEvent::WindowTitleChange: {
            QWidget *pWidget = qobject_cast<QWidget *>(obj);
            if (pWidget) {
                title_label_->setText(pWidget->windowTitle());
                return true;
            }
            return false;
        }
        case QEvent::WindowIconChange: {
            QWidget *pWidget = qobject_cast<QWidget *>(obj);
            if (pWidget) {
                QIcon icon = pWidget->windowIcon();
                icon_label_->setPixmap(icon.pixmap(icon_label_->size()));
                return true;
            }
            return false;
        }
        case QEvent::WindowStateChange:
        case QEvent::Resize:
            this->updateMaximize();
            return true;
        default:
            return QWidget::eventFilter(obj, event);
        }
    }

  public:
    /// 标题栏的按钮状态
    // 二进制最后一位为1表示close开
    // 倒数第二位为1表示max开
    // 倒数第三位为1表示min开
    enum Buttons { CLOSE = 1, CLOSE_MAX = 3, CLOSE_MIN = 5, ALL = 7 };
    /// <summary> parent不能为空. </summary>
    /// <param name: button> 用于选择最大化以及最小化按钮是否添加. </param>
    explicit TitleBar(QWidget *parent, Buttons button = ALL)
        : QWidget(parent) {
        assert(parent && "the parent of titlebar cannot be empty");

        is_pressed_ = false;

        this->resize(parent->width(), TITLE_BAR_HEIGHT);
        this->setFixedHeight(TITLE_BAR_HEIGHT);
        initMaxIcons(button);
        initWidgets(button);
        initLayout(button);
        initConnection(button);
    }

    /// <summary> 以传入参数设置title</summary>
    virtual void setTitle(const QString &title) {
        title_label_->setText(title);
    }

    /// <summary> 以传入的icon设置TitleBar的icon </summary>
    virtual void setTitleIcon(const QIcon &icon) {
        icon_label_->setPixmap(icon.pixmap(icon_label_->size()));
    }

    /// <summary> 以传入的icon设置TitleBar的背景</summary>
    virtual void setBackground(const QIcon &icon) {
        this->setAutoFillBackground(true);
        QPalette palette;

        palette.setBrush(backgroundRole(), QBrush(icon.pixmap(this->size())));

        this->setPalette(palette);
    }

    virtual ~TitleBar() {
        // 因为很多成员都是以titlebar为parent的, 所以会自动析构.
        // 这里不需要手动delete
        max_max_normal_  = nullptr;
        max_max_focus_   = nullptr;
        max_max_pressed_ = nullptr;

        max_normal_normal_  = nullptr;
        max_normal_focus_   = nullptr;
        max_normal_pressed_ = nullptr;
    }

  private slots:
    void onButtonClicked() {
        QPushButton *pButton = qobject_cast<QPushButton *>(sender());
        QWidget *    pWindow = this->window();
        if (pWindow->isTopLevel()) {
            if (pButton == pminimize_button_) {
                pWindow->showMinimized();
            } else if (pButton == pmaximize_button_) {
                pWindow->isMaximized() ? pWindow->showNormal()
                                       : pWindow->showMaximized();

                this->updateMaximize();
            } else if (pButton == pclose_button_) {
                pWindow->close();
            }
        }
    }
};
} // namespace lon

#endif