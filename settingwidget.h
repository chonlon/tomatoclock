#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include "lon_widget/widget.hpp"
#include "ui_settingwidget.h"
#include "clockoptions.hpp"
#include <QWidget>

namespace Ui {
class SettingWidgetPrivate;
}

class SettingWidgetPrivate : public QWidget {
    Q_OBJECT
    public:
    explicit SettingWidgetPrivate(QWidget *parent = nullptr) : QWidget(parent),
    ui(new Ui::SettingWidgetPrivate)
    {
        ui->setupUi(this);
		setSliderQss(ui->work_slider_p_, "#E8EDF2", "#1ABC9C", "#1ABC9C");
		setSliderQss(ui->shortbreak_slider_p_, "#E8EDF2", "#1ABC9C", "#1ABC9C");
		setSliderQss(ui->long_break_slider_p_, "#E8EDF2", "#1ABC9C", "#1ABC9C");
		// ÉèÖÃtextedit±³¾°Í¸Ã÷.
		ui->plainTextEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    }
	~SettingWidgetPrivate() { delete ui; }
    lon::ClockOptions *clockOptionSetted() const {
        return clock_option_setted_p_;
    }
  private:
    void setSliderQss(QSlider *slider, QString normal_color, QString groove_color,
                 QString handle_color) {
        int         sliderHeight = 8;
        int         sliderRadius = 4;
        int         handleWidth  = 13;
        int         handleRadius = 6;
        int         handleOffset = 3;
        QStringList qss;
        qss.append(
            QString("QSlider::groove:horizontal,QSlider::add-page:horizontal{"
                    "height:%2px;border-radius:%3px;background:%1;}")
                .arg(normal_color)
                .arg(sliderHeight)
                .arg(sliderRadius));
        qss.append(QString("QSlider::sub-page:horizontal{height:%2px;border-"
                           "radius:%3px;background:%1;}")
                       .arg(groove_color)
                       .arg(sliderHeight)
                       .arg(sliderRadius));
        qss.append(
            QString("QSlider::handle:horizontal{width:%2px;margin-top:-%3px;"
                    "margin-bottom:-%3px;border-radius:%4px;"
                    "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,"
                    "radius:0.5,fx:0.5,fy:0.5,stop:0.6 #FFFFFF,stop:0.8 %1);}")
                .arg(handle_color)
                .arg(handleWidth)
                .arg(handleOffset)
                .arg(handleRadius));
        qss.append(
			QString("QSlider::handle:horizontal:hover{width:%1px;margin-top:-%2px;"
				"margin-bottom:-%2px;border-radius:%3px;"
				"background:qradialgradient(spread:pad,cx:0.5,cy:0.5,"
                    "radius:0.5,fx:0.5,fy:0.5,stop:0.6 #FFFFFF,stop:0.8 rgba(30, 30, 30));}")
                .arg(handleWidth)
                .arg(handleOffset)
                .arg(handleRadius));
        slider->setStyleSheet(qss.join(""));
    }
	Ui::SettingWidgetPrivate *ui;

	lon::ClockOptions *clock_option_setted_p_;
};

class SettingWidget : public lon::Widget {
    Q_OBJECT
  public:
    explicit SettingWidget(QWidget *parent = nullptr);
	~SettingWidget() = default;

  private:
    SettingWidgetPrivate *widget_p_;
	lon::ClockOptions *clock_option_setted_p_;

	void saveSettingToFile();
public slots:
    void closingWindow() {}
};

#endif // SETTINGWIDGET_H
