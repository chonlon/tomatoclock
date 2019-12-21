#include "progresswidget.h"

lon::clock_window::ProgressWidget::ProgressWidget(QWidget* parent)
    : DisplayClockBase(parent) {
    qWarning() << "it is not wished that do not set widget width and height";
    // throw std::logic_error("wish to set height and width");
}

lon::clock_window::ProgressWidget::ProgressWidget(uint16_t height,
                                                  uint16_t width,
                                                  QWidget* parent)
    : DisplayClockBase(parent) {
    height_ = height;
    width_ = width;

    scene_ = new QGraphicsScene(this);
    view_ = new QGraphicsView(scene_, this);
    current_progress_ = nullptr;
    time_label_ = new QLabel(this);

    layout_ = new QHBoxLayout(this);
    view_layout_ = new QHBoxLayout(view_);

    layout_->setContentsMargins(0, 0, 0, 0);
    view_layout_->setContentsMargins(0, 0, 0, 0);

    pen_ = new QPen(QColor(255, 255, 255, 10));
    pen_->setWidth(0);

    QFont ft("Microsoft YaHei", 20);
    // ft.setPointSize(11);
    time_label_->setFont(ft);
    time_label_->setFixedSize(width_, height_);
    time_label_->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    view_->setFixedSize(width_, height_);
    this->setStyleSheet(
        "QWidget {\
                       background-color: rgba(248, 247, 216, 0.1);}");

    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_layout_->addWidget(time_label_);
    view_->setLayout(view_layout_);

    current_progress_ = scene_->addRect(-1 * width_,
                                        0,
                                        width_,
                                        height_,
                                        *pen_,
                                        *working_foreground_brush_);
    // layout_->addWidget(view_);
}

lon::clock_window::ProgressWidget::~ProgressWidget() { delete pen_; }

void lon::clock_window::ProgressWidget::updateTimeDisplay(
    TimerStatus const* timer_status) {
    ClockTime const* total_time = timer_status->getTotalTime();
    int current_progress_width =
        static_cast<int>(currentPersent(timer_status) * width_);

    if (total_time_ != total_time) {
        if (current_progress_ != nullptr)
            scene_->removeItem(current_progress_);
        if (total_time == timer_status->clock_options()->work_time()) {
            current_progress_ =
                scene_->addRect(-1 * width_,
                                0,
                                width_,
                                height_,
                                *pen_,
                                *working_foreground_brush_);
        } else if (total_time == timer_status->clock_options()->sb_time()) {
            current_progress_ =
                scene_->addRect(-1 * width_,
                                0,
                                width_,
                                height_,
                                *pen_,
                                *shortbreaking_foreground_brush_);
        } else {
            current_progress_ =
                scene_->addRect(-1 * width_,
                                0,
                                width_,
                                height_,
                                *pen_,
                                *longbreaking_foreground_brush_);
        }
        total_time_ = total_time;
    }

    current_progress_->setPos(-1 * width_ + current_progress_width, 0);
    time_label_->setText(*leftTimeString(timer_status));
}
