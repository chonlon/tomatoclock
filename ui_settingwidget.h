/********************************************************************************
** Form generated from reading UI file 'settingwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGWIDGET_H
#define UI_SETTINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingWidgetPrivate
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *main_layout_p_;
    QGridLayout *gridlayout_top_p_;
    QLabel *time_remind_label_p_;
    QFrame *line;
    QSpacerItem *spacer_left_p_;
    QVBoxLayout *time_setting_layout_p_;
    QLabel *work_remind_label_p;
    QHBoxLayout *horizontalLayout_1;
    QSpacerItem *spacer_1_1_p_;
    QVBoxLayout *verticallayout_p_;
    QSlider *work_slider_p_;
    QLabel *work_label_p_;
    QSpacerItem *spacer_1_2_p_;
    QLabel *shortbreak_remind_label_p;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *spacer_2_1_p_;
    QVBoxLayout *verticallayout_2_p_;
    QSlider *shortbreak_slider_p_;
    QLabel *short_break_p_;
    QSpacerItem *spacer_2_2_p_;
    QLabel *longbreak_remind_label_p;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *spacer_3_1_p_;
    QVBoxLayout *verticallayout_3_p_;
    QSlider *long_break_slider_p_;
    QLabel *long_break_label_p_;
    QSpacerItem *spacer_3_2_p_;
    QLabel *break_time_label_p;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *spacer_4_1_p_;
    QVBoxLayout *verticallayout_3_p_1;
    QSlider *break_time_slider_p_;
    QLabel *break_time_label_p_;
    QSpacerItem *spacer_4_2_p_;
    QGridLayout *gridLayout_3;
    QLabel *other_setting_label_p_;
    QFrame *line_bottom_p_;
    QSpacerItem *spacer_bottom_left_p_;
    QGridLayout *gridLayout_2;
    QSpacerItem *spacer_bottom_right_p_;
    QPlainTextEdit *plainTextEdit;
    QCheckBox *checkBox;

    void setupUi(QWidget *SettingWidgetPrivate)
    {
        if (SettingWidgetPrivate->objectName().isEmpty())
            SettingWidgetPrivate->setObjectName(QString::fromUtf8("SettingWidgetPrivate"));
        SettingWidgetPrivate->resize(873, 609);
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font.setItalic(false);
        SettingWidgetPrivate->setFont(font);
        verticalLayout = new QVBoxLayout(SettingWidgetPrivate);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        main_layout_p_ = new QVBoxLayout();
        main_layout_p_->setSpacing(6);
        main_layout_p_->setObjectName(QString::fromUtf8("main_layout_p_"));
        gridlayout_top_p_ = new QGridLayout();
        gridlayout_top_p_->setSpacing(6);
        gridlayout_top_p_->setObjectName(QString::fromUtf8("gridlayout_top_p_"));
        time_remind_label_p_ = new QLabel(SettingWidgetPrivate);
        time_remind_label_p_->setObjectName(QString::fromUtf8("time_remind_label_p_"));
        time_remind_label_p_->setFont(font);

        gridlayout_top_p_->addWidget(time_remind_label_p_, 0, 0, 1, 2);

        line = new QFrame(SettingWidgetPrivate);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridlayout_top_p_->addWidget(line, 1, 0, 1, 2);

        spacer_left_p_ = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridlayout_top_p_->addItem(spacer_left_p_, 2, 0, 1, 1);

        time_setting_layout_p_ = new QVBoxLayout();
        time_setting_layout_p_->setSpacing(6);
        time_setting_layout_p_->setObjectName(QString::fromUtf8("time_setting_layout_p_"));
        work_remind_label_p = new QLabel(SettingWidgetPrivate);
        work_remind_label_p->setObjectName(QString::fromUtf8("work_remind_label_p"));
        work_remind_label_p->setFont(font);

        time_setting_layout_p_->addWidget(work_remind_label_p);

        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setSpacing(6);
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        spacer_1_1_p_ = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_1->addItem(spacer_1_1_p_);

        verticallayout_p_ = new QVBoxLayout();
        verticallayout_p_->setSpacing(6);
        verticallayout_p_->setObjectName(QString::fromUtf8("verticallayout_p_"));
        work_slider_p_ = new QSlider(SettingWidgetPrivate);
        work_slider_p_->setObjectName(QString::fromUtf8("work_slider_p_"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(work_slider_p_->sizePolicy().hasHeightForWidth());
        work_slider_p_->setSizePolicy(sizePolicy);
        work_slider_p_->setMaximumSize(QSize(200, 16777215));
        work_slider_p_->setCursor(QCursor(Qt::PointingHandCursor));
        work_slider_p_->setStyleSheet(QString::fromUtf8(""));
        work_slider_p_->setMinimum(10);
        work_slider_p_->setMaximum(50);
        work_slider_p_->setSliderPosition(25);
        work_slider_p_->setOrientation(Qt::Horizontal);

        verticallayout_p_->addWidget(work_slider_p_);

        work_label_p_ = new QLabel(SettingWidgetPrivate);
        work_label_p_->setObjectName(QString::fromUtf8("work_label_p_"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(work_label_p_->sizePolicy().hasHeightForWidth());
        work_label_p_->setSizePolicy(sizePolicy1);
        work_label_p_->setMaximumSize(QSize(200, 16777215));
        QFont font1;
        font1.setItalic(false);
        work_label_p_->setFont(font1);
        work_label_p_->setAlignment(Qt::AlignCenter);

        verticallayout_p_->addWidget(work_label_p_);


        horizontalLayout_1->addLayout(verticallayout_p_);

        spacer_1_2_p_ = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_1->addItem(spacer_1_2_p_);


        time_setting_layout_p_->addLayout(horizontalLayout_1);

        shortbreak_remind_label_p = new QLabel(SettingWidgetPrivate);
        shortbreak_remind_label_p->setObjectName(QString::fromUtf8("shortbreak_remind_label_p"));
        shortbreak_remind_label_p->setFont(font);

        time_setting_layout_p_->addWidget(shortbreak_remind_label_p);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        spacer_2_1_p_ = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(spacer_2_1_p_);

        verticallayout_2_p_ = new QVBoxLayout();
        verticallayout_2_p_->setSpacing(6);
        verticallayout_2_p_->setObjectName(QString::fromUtf8("verticallayout_2_p_"));
        shortbreak_slider_p_ = new QSlider(SettingWidgetPrivate);
        shortbreak_slider_p_->setObjectName(QString::fromUtf8("shortbreak_slider_p_"));
        shortbreak_slider_p_->setMaximumSize(QSize(200, 16777215));
        shortbreak_slider_p_->setStyleSheet(QString::fromUtf8(""));
        shortbreak_slider_p_->setMinimum(1);
        shortbreak_slider_p_->setMaximum(20);
        shortbreak_slider_p_->setSliderPosition(5);
        shortbreak_slider_p_->setOrientation(Qt::Horizontal);

        verticallayout_2_p_->addWidget(shortbreak_slider_p_);

        short_break_p_ = new QLabel(SettingWidgetPrivate);
        short_break_p_->setObjectName(QString::fromUtf8("short_break_p_"));
        short_break_p_->setMaximumSize(QSize(200, 16777215));
        short_break_p_->setFont(font1);
        short_break_p_->setAlignment(Qt::AlignCenter);

        verticallayout_2_p_->addWidget(short_break_p_);


        horizontalLayout_2->addLayout(verticallayout_2_p_);

        spacer_2_2_p_ = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(spacer_2_2_p_);


        time_setting_layout_p_->addLayout(horizontalLayout_2);

        longbreak_remind_label_p = new QLabel(SettingWidgetPrivate);
        longbreak_remind_label_p->setObjectName(QString::fromUtf8("longbreak_remind_label_p"));
        longbreak_remind_label_p->setFont(font);

        time_setting_layout_p_->addWidget(longbreak_remind_label_p);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        spacer_3_1_p_ = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacer_3_1_p_);

        verticallayout_3_p_ = new QVBoxLayout();
        verticallayout_3_p_->setSpacing(6);
        verticallayout_3_p_->setObjectName(QString::fromUtf8("verticallayout_3_p_"));
        long_break_slider_p_ = new QSlider(SettingWidgetPrivate);
        long_break_slider_p_->setObjectName(QString::fromUtf8("long_break_slider_p_"));
        long_break_slider_p_->setMaximumSize(QSize(200, 16777215));
        long_break_slider_p_->setStyleSheet(QString::fromUtf8(""));
        long_break_slider_p_->setMinimum(5);
        long_break_slider_p_->setMaximum(30);
        long_break_slider_p_->setSliderPosition(15);
        long_break_slider_p_->setOrientation(Qt::Horizontal);

        verticallayout_3_p_->addWidget(long_break_slider_p_);

        long_break_label_p_ = new QLabel(SettingWidgetPrivate);
        long_break_label_p_->setObjectName(QString::fromUtf8("long_break_label_p_"));
        long_break_label_p_->setMaximumSize(QSize(200, 16777215));
        long_break_label_p_->setFont(font1);
        long_break_label_p_->setAlignment(Qt::AlignCenter);

        verticallayout_3_p_->addWidget(long_break_label_p_);


        horizontalLayout->addLayout(verticallayout_3_p_);

        spacer_3_2_p_ = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacer_3_2_p_);


        time_setting_layout_p_->addLayout(horizontalLayout);

        break_time_label_p = new QLabel(SettingWidgetPrivate);
        break_time_label_p->setObjectName(QString::fromUtf8("break_time_label_p"));

        time_setting_layout_p_->addWidget(break_time_label_p);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        spacer_4_1_p_ = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(spacer_4_1_p_);

        verticallayout_3_p_1 = new QVBoxLayout();
        verticallayout_3_p_1->setSpacing(6);
        verticallayout_3_p_1->setObjectName(QString::fromUtf8("verticallayout_3_p_1"));
        break_time_slider_p_ = new QSlider(SettingWidgetPrivate);
        break_time_slider_p_->setObjectName(QString::fromUtf8("break_time_slider_p_"));
        break_time_slider_p_->setMaximumSize(QSize(200, 16777215));
        break_time_slider_p_->setStyleSheet(QString::fromUtf8(""));
        break_time_slider_p_->setMinimum(2);
        break_time_slider_p_->setMaximum(10);
        break_time_slider_p_->setValue(3);
        break_time_slider_p_->setSliderPosition(3);
        break_time_slider_p_->setOrientation(Qt::Horizontal);

        verticallayout_3_p_1->addWidget(break_time_slider_p_);

        break_time_label_p_ = new QLabel(SettingWidgetPrivate);
        break_time_label_p_->setObjectName(QString::fromUtf8("break_time_label_p_"));
        break_time_label_p_->setMaximumSize(QSize(200, 16777215));
        break_time_label_p_->setFont(font1);
        break_time_label_p_->setAlignment(Qt::AlignCenter);

        verticallayout_3_p_1->addWidget(break_time_label_p_);


        horizontalLayout_3->addLayout(verticallayout_3_p_1);

        spacer_4_2_p_ = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(spacer_4_2_p_);


        time_setting_layout_p_->addLayout(horizontalLayout_3);


        gridlayout_top_p_->addLayout(time_setting_layout_p_, 2, 1, 1, 1);


        main_layout_p_->addLayout(gridlayout_top_p_);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        other_setting_label_p_ = new QLabel(SettingWidgetPrivate);
        other_setting_label_p_->setObjectName(QString::fromUtf8("other_setting_label_p_"));
        other_setting_label_p_->setFont(font1);

        gridLayout_3->addWidget(other_setting_label_p_, 0, 0, 1, 2);

        line_bottom_p_ = new QFrame(SettingWidgetPrivate);
        line_bottom_p_->setObjectName(QString::fromUtf8("line_bottom_p_"));
        line_bottom_p_->setFrameShape(QFrame::HLine);
        line_bottom_p_->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_bottom_p_, 1, 0, 1, 2);

        spacer_bottom_left_p_ = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_3->addItem(spacer_bottom_left_p_, 2, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        spacer_bottom_right_p_ = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(spacer_bottom_right_p_, 1, 0, 1, 1);

        plainTextEdit = new QPlainTextEdit(SettingWidgetPrivate);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Microsoft JhengHei UI Light"));
        font2.setItalic(true);
        plainTextEdit->setFont(font2);
        plainTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextEdit->setReadOnly(true);
        plainTextEdit->setBackgroundVisible(false);

        gridLayout_2->addWidget(plainTextEdit, 1, 1, 1, 1);

        checkBox = new QCheckBox(SettingWidgetPrivate);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setFont(font1);

        gridLayout_2->addWidget(checkBox, 0, 0, 1, 2);


        gridLayout_3->addLayout(gridLayout_2, 2, 1, 1, 1);


        main_layout_p_->addLayout(gridLayout_3);


        verticalLayout->addLayout(main_layout_p_);


        retranslateUi(SettingWidgetPrivate);

        QMetaObject::connectSlotsByName(SettingWidgetPrivate);
    } // setupUi

    void retranslateUi(QWidget *SettingWidgetPrivate)
    {
        SettingWidgetPrivate->setWindowTitle(QApplication::translate("SettingWidgetPrivate", "Translate", nullptr));
        time_remind_label_p_->setText(QApplication::translate("SettingWidgetPrivate", "\346\227\266\351\225\277\350\256\276\347\275\256", nullptr));
        work_remind_label_p->setText(QApplication::translate("SettingWidgetPrivate", "\345\267\245\344\275\234\346\227\266\351\225\277", nullptr));
        work_label_p_->setText(QApplication::translate("SettingWidgetPrivate", "25 : 00", nullptr));
        shortbreak_remind_label_p->setText(QApplication::translate("SettingWidgetPrivate", "\347\237\255\344\274\221\346\201\257\346\227\266\351\225\277", nullptr));
        short_break_p_->setText(QApplication::translate("SettingWidgetPrivate", "5 : 00", nullptr));
        longbreak_remind_label_p->setText(QApplication::translate("SettingWidgetPrivate", "\351\225\277\344\274\221\346\201\257\346\227\266\351\225\277", nullptr));
        long_break_label_p_->setText(QApplication::translate("SettingWidgetPrivate", "15 : 00", nullptr));
        break_time_label_p->setText(QApplication::translate("SettingWidgetPrivate", "\346\257\217\351\232\224\345\244\232\345\260\221\344\270\252\346\256\265\344\274\221\346\201\257\350\277\233\350\241\214\344\270\200\346\254\241\351\225\277\344\274\221\346\201\257", nullptr));
        break_time_label_p_->setText(QApplication::translate("SettingWidgetPrivate", "3", nullptr));
        other_setting_label_p_->setText(QApplication::translate("SettingWidgetPrivate", "\345\205\266\344\273\226\350\256\276\347\275\256", nullptr));
        plainTextEdit->setPlainText(QApplication::translate("SettingWidgetPrivate", "\350\256\276\347\275\256\350\277\236\347\273\255\345\267\245\344\275\234\346\204\217\345\221\263\347\235\200\346\257\217\344\270\252\347\225\252\350\214\204\351\222\237\347\273\223\346\235\237\344\274\232\350\207\252\345\212\250\345\274\200\345\247\213\344\270\213\344\270\200\344\270\252\347\225\252\350\214\204\351\222\237\343\200\202\345\274\200\345\220\257\346\255\244\351\241\271\345\220\216\357\274\214\345\246\202\346\236\234\345\234\250\346\237\220\344\270\252\347\225\252\350\214\204\351\222\237\347\273\223\346\235\237\345\220\216\346\203\263\345\201\234\346\255\242\345\267\245\344\275\234\357\274\214\345\217\252\350\203\275\346\217\220\345\211\215\347\273\223\346\235\237\350\207\252\345\212\250\345\274\200\345\247\213\347\232\204\347\225\252\350\214\204\357\274\214\344\270\215\350\277\207\357\274\214\346\234\252\346\273\2412\345\210\206\351\222\237\347\232\204\347\225\252\350\214\204\346\230\257\344\270\215\344\274\232\350\256\260\345\275\225\347\232\204\343\200\202", nullptr));
        checkBox->setText(QApplication::translate("SettingWidgetPrivate", "\346\230\257\345\220\246\350\277\236\347\273\255\345\267\245\344\275\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingWidgetPrivate: public Ui_SettingWidgetPrivate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWIDGET_H
