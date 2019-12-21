#include "clockdisplaywidget.h"

lon::ClockDisplayWidget::ClockDisplayWidget(QWidget* parent)
    : DisplayClockBase(parent),
      left_time_string_p_(new QString()) {
    current_persent_ = 0;
    current_brush_ = working_foreground_brush_;
    total_time_ = nullptr;
}

void lon::ClockDisplayWidget::updateTimeDisplay(
    const TimerStatus* timer_status) {
    timer_status_ = timer_status;
    ClockTime const* total_time = timer_status->getTotalTime();
    current_persent_ = currentPersent(timer_status);
    left_time_string_p_ = leftTimeString(timer_status);
    if (total_time_ != total_time) {
        if (total_time == timer_status->clock_options()->work_time()) {
            current_brush_ = working_foreground_brush_;
        } else if (total_time == timer_status->clock_options()->sb_time()) {
            current_brush_ = shortbreaking_foreground_brush_;
        } else {
            current_brush_ = longbreaking_foreground_brush_;
        }
        total_time_ = total_time;
    }
    update();
}

void lon::ClockDisplayWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    double m_rotateAngle = current_persent_ * 360.0;

    int side = qMin(width(), height()) - 10;
    QRectF outRect(5, 5, side, side);
    //    QRectF inRect(20, 20, side-40, side-40);
    //画外圆
    // current_brush_->color()
    p.setPen(QPen(current_brush_->color(), 10));

    p.drawArc(outRect, (90 - m_rotateAngle) * 16, m_rotateAngle * 16);

    //画文字
    if (left_time_string_p_ == nullptr)
        return;
    QFont f = QFont("Microsoft YaHei", 15, QFont::Bold);
    p.setFont(f);
    p.drawText(outRect, Qt::AlignCenter, *left_time_string_p_);
}
