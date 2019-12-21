#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include "clockoptions.hpp"
#include "lon_widget/widget.hpp"
#include "settingfileoperations.h"
#include "ui_settingwidget.h"
#include <QWidget>

namespace Ui {
class SettingWidgetPrivate;
}

class SettingWidgetPrivate : public QWidget {
    Q_OBJECT
public:
    explicit SettingWidgetPrivate(QWidget* parent = nullptr)
        : QWidget(parent), ui(new Ui::SettingWidgetPrivate) {
        ui->setupUi(this);
        clock_option_setted_p_ =
            new lon::ClockOptions(SettingFileOperations().readClockOptionFromFile());
        setSliderQss(ui->work_slider_p_, "#E8EDF2", "#1ABC9C", "#1ABC9C");
        setSliderQss(ui->shortbreak_slider_p_, "#E8EDF2", "#1ABC9C", "#1ABC9C");
        setSliderQss(ui->long_break_slider_p_, "#E8EDF2", "#1ABC9C", "#1ABC9C");
        setSliderQss(ui->break_time_slider_p_, "#E8EDF2", "#1ABC9C", "#1ABC9C");

        // 设置textedit背景透明.
        ui->plainTextEdit->setStyleSheet(
            "background:transparent;border-width:0;border-style:outset");

        connect(ui->work_slider_p_, SIGNAL(valueChanged(int)), this, SLOT(setWorkTimeLabel(int)));
        connect(ui->shortbreak_slider_p_,
                SIGNAL(valueChanged(int)),
                this,
                SLOT(setShortbreakLabel(int)));
        connect(ui->long_break_slider_p_,
                SIGNAL(valueChanged(int)),
                this,
                SLOT(setLongbreakLabel(int)));
        connect(ui->break_time_slider_p_,
                SIGNAL(valueChanged(int)),
                this,
                SLOT(setBreakTimeLabel(int)));
        connect(ui->check_box_p_, SIGNAL(stateChanged(int)), this, SLOT(setKeepWorking(int)));
        ui->work_slider_p_->setValue(clock_option_setted_p_->work_time()->minutes_);
        ui->shortbreak_slider_p_->setValue(clock_option_setted_p_->sb_time()->minutes_);
        ui->long_break_slider_p_->setValue(clock_option_setted_p_->lb_time()->minutes_);
        ui->break_time_slider_p_->setValue(clock_option_setted_p_->sbtimes_between_lb());
        ui->check_box_p_->setCheckState(clock_option_setted_p_->keepWorking() ? Qt::Checked
                                                                              : Qt::Unchecked);
        // setWorkTimeLabel(clock_option_setted_p_->work_time()->minutes_);
        // setShortbreakLabel(clock_option_setted_p_->sb_time()->minutes_);
        // setLongbreakLabel(clock_option_setted_p_->lb_time()->minutes_);
    }

    ~SettingWidgetPrivate() {
        delete ui;
    }

    lon::ClockOptions* clockOptionSetted() const {
        return clock_option_setted_p_;
    }

public slots:
    void setWorkTimeLabel(int value) {
        QString num = QString::number(value);
        num.append(" : 00");
        ui->work_label_p_->setText(num);
        clock_option_setted_p_->setWorkTime(value, 0);
    }

    void setShortbreakLabel(int value) {
        QString num = QString::number(value);
        num.append(" : 00");
        ui->short_break_p_->setText(num);
        clock_option_setted_p_->setShortBreakTime(value, 0);
    }

    void setLongbreakLabel(int value) {
        QString num = QString::number(value);
        num.append(" : 00");
        ui->long_break_label_p_->setText(num);
        clock_option_setted_p_->setLongBreakTime(value, 0);
    }

    void setBreakTimeLabel(int value) {
        ui->break_time_label_p_->setText(QString::number(value));
        clock_option_setted_p_->set_sbtimes_between_lb(value);
    }

    void setKeepWorking(int val) {
        clock_option_setted_p_->setKeepWorking(static_cast<bool>(val));
    }

private:
    void setSliderQss(QSlider* slider,
                      QString normal_color,
                      QString groove_color,
                      QString handle_color) {
        int sliderHeight = 8;
        int sliderRadius = 4;
        int handleWidth = 13;
        int handleRadius = 6;
        int handleOffset = 3;
        QStringList qss;
        qss.append(QString("QSlider::groove:horizontal,QSlider::add-page:horizontal{"
                           "height:%2px;border-radius:%3px;background:%1;}")
                       .arg(normal_color)
                       .arg(sliderHeight)
                       .arg(sliderRadius));
        qss.append(QString("QSlider::sub-page:horizontal{height:%2px;border-"
                           "radius:%3px;background:%1;}")
                       .arg(groove_color)
                       .arg(sliderHeight)
                       .arg(sliderRadius));
        qss.append(QString("QSlider::handle:horizontal{width:%2px;margin-top:-%3px;"
                           "margin-bottom:-%3px;border-radius:%4px;"
                           "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,"
                           "radius:0.5,fx:0.5,fy:0.5,stop:0.6 #FFFFFF,stop:0.8 %1);}")
                       .arg(handle_color)
                       .arg(handleWidth)
                       .arg(handleOffset)
                       .arg(handleRadius));
        qss.append(QString("QSlider::handle:horizontal:hover{width:%1px;margin-top:-%2px;"
                           "margin-bottom:-%2px;border-radius:%3px;"
                           "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,"
                           "radius:0.5,fx:0.5,fy:0.5,stop:0.6 #FFFFFF,stop:0.8 rgba(30, "
                           "30, 30));}")
                       .arg(handleWidth)
                       .arg(handleOffset)
                       .arg(handleRadius));
        slider->setStyleSheet(qss.join(""));
    }

    Ui::SettingWidgetPrivate* ui;

    lon::ClockOptions* clock_option_setted_p_;
};

class SettingWidget : public lon::Widget {
    Q_OBJECT
public:
    explicit SettingWidget(QWidget* parent = nullptr);
    ~SettingWidget() = default;

private:
    SettingWidgetPrivate* widget_p_;
    lon::ClockOptions* clock_option_setted_p_;

signals:
    void settingChanged(lon::ClockOptions);
public slots:
    void closingWindow();
};

#endif  // SETTINGWIDGET_H
