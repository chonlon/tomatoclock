#include "clocksmallwindow.h"

// TODO 添加此窗口的设置透明度(ctrl + 滑轮).
lon::clock_window::ClockSmallWindow::ClockSmallWindow(
    const QString& label_name,
    const QString& target_name,
    QWidget* parent)
    : QWidget(parent),
      fixed_height_(70),
      fixed_width_(300) {
    layout_ = new QHBoxLayout(this);
    window_background_ = new QPixmap(":/all/1111.png");

    progress_widget_ = new ProgressWidget(fixed_height_, fixed_width_, this);
    tools_widget_ = new ToolsWidget(label_name, target_name, this);
    tools_widget_->resize(fixed_width_, fixed_height_);
    tools_widget_->setVisible(false);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint |
        Qt::WindowMinimizeButtonHint |
        Qt::WindowStaysOnTopHint);

    layout_->setContentsMargins(0, 0, 0, 0);
    layout_->addWidget(progress_widget_);

    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(*window_background_));

    this->setPalette(palette);
    this->setFixedSize(fixed_width_, fixed_height_);
    this->setLayout(layout_);

    connect(tools_widget_,
            SIGNAL(stopButtonClicked()),
            this,
            SIGNAL(clockStoped()));
    connect(tools_widget_,
            SIGNAL(closeButtonClicked()),
            this,
            SIGNAL(smallWindowClosing()));
}

void lon::clock_window::ClockSmallWindow::enterEvent(QEvent* event) {
    layout_->removeWidget(progress_widget_);
    progress_widget_->setVisible(false);
    layout_->addWidget(tools_widget_);
    tools_widget_->setVisible(true);
}

void lon::clock_window::ClockSmallWindow::leaveEvent(QEvent* event) {
    layout_->removeWidget(tools_widget_);
    tools_widget_->setVisible(false);
    layout_->addWidget(progress_widget_);
    progress_widget_->setVisible(true);
}

void lon::clock_window::ClockSmallWindow::mousePressEvent(QMouseEvent* event) {
    if (this->window()->isMaximized())
        return;

    is_pressed_ = true;
    move_start_position_ = event->globalPos();
    return QWidget::mousePressEvent(event);
}

void lon::clock_window::ClockSmallWindow::mouseMoveEvent(QMouseEvent* event) {
    if (!is_pressed_)
        return;

    QPoint move_point = event->globalPos() - move_start_position_;
    QPoint widget_pos = this->window()->pos();

    move_start_position_ = event->globalPos();
    this->window()->move(widget_pos.x() + move_point.x(),
                         widget_pos.y() + move_point.y());
    return QWidget::mouseMoveEvent(event);
}

void lon::clock_window::ClockSmallWindow::mouseReleaseEvent(
    QMouseEvent* event) {
    is_pressed_ = false;
    return QWidget::mouseReleaseEvent(event);
}

void lon::clock_window::ClockSmallWindow::wheelEvent(QWheelEvent* event) {
    auto delta = event->delta();
    if (delta > 0) {
        this->setWindowOpacity(this->windowOpacity() + 0.05);
    } else {
        this->setWindowOpacity(this->windowOpacity() - 0.05);
    }
}

lon::clock_window::ClockSmallWindow::~ClockSmallWindow() {
    delete window_background_;
}
