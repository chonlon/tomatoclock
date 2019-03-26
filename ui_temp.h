/********************************************************************************
** Form generated from reading UI file 'temp.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMP_H
#define UI_TEMP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_temp
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QDialogButtonBox *buttonBox;
    QScrollBar *verticalScrollBar;

    void setupUi(QWidget *temp)
    {
        if (temp->objectName().isEmpty())
            temp->setObjectName(QString::fromUtf8("temp"));
        temp->resize(1031, 613);
        horizontalLayout = new QHBoxLayout(temp);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(temp);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("border-image: url(:/background/1111.png);"));

        horizontalLayout->addWidget(widget);

        buttonBox = new QDialogButtonBox(temp);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);

        verticalScrollBar = new QScrollBar(temp);
        verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
        verticalScrollBar->setStyleSheet(QString::fromUtf8("QScrollBar:vertical\n"
"{\n"
"    border-radius:4px;\n"
"    background: white;\n"
"    width: 10px;\n"
"    margin: 0px 0px 0 0px;\n"
"}\n"
"QScrollBar:vertical:hover\n"
"{\n"
"    border-radius:4px;\n"
"    background: rgb(228,228,228);\n"
"    width: 10px;\n"
"    margin: 0px 0px 0 0px;\n"
"}\n"
" \n"
"QScrollBar::handle:vertical \n"
"{\n"
"    background: rgb(202,202,202);\n"
"    border-radius:4px;\n"
"    min-height: 20px;\n"
"}\n"
"QScrollBar::handle:vertical:hover\n"
"{\n"
"    background: rgb(113,113,113);\n"
"    border-radius:4px;\n"
"    min-height: 20px;\n"
"}\n"
" \n"
"QScrollBar::add-line:vertical \n"
"{\n"
"    background: none;\n"
"    height: 10px;\n"
"    subcontrol-position: bottom;\n"
"    subcontrol-origin: margin;\n"
"}\n"
" \n"
"QScrollBar::sub-line:vertical \n"
"{\n"
"    background: none;\n"
"    height: 10px;\n"
"    subcontrol-position: top;\n"
"    subcontrol-origin: margin;\n"
"}\n"
" \n"
"QScrollBar::up-arrow:vertical\n"
"{\n"
"    width: 10px;\n"
"    height: 10px;\n"
"    backg"
                        "round: url(:/ScrollBar/ScrollBar/scrollbar_arrowup_normal.png);\n"
"}\n"
"QScrollBar::up-arrow:vertical:hover\n"
"{\n"
"    width: 10px;\n"
"    height: 10px;\n"
"    background: url(:/ScrollBar/ScrollBar/scrollbar_arrowup_highlight.png);\n"
"}\n"
"QScrollBar::up-arrow:vertical:pressed\n"
"{\n"
"    width: 10px;\n"
"    height: 10px;\n"
"    background: url(:/ScrollBar/ScrollBar/scrollbar_arrowup_down.png);\n"
"}\n"
" \n"
"QScrollBar::down-arrow:vertical \n"
"{\n"
"    width: 10px;\n"
"    height: 10px;\n"
"    background: url(:/ScrollBar/ScrollBar/scrollbar_arrowdown_normal.png);\n"
"}\n"
"QScrollBar::down-arrow:vertical:hover\n"
"{\n"
"    width: 10px;\n"
"    height: 10px;\n"
"    background: url(:/ScrollBar/ScrollBar/scrollbar_arrowdown_highlight.png);\n"
"}\n"
"QScrollBar::down-arrow:vertical:pressed\n"
"{\n"
"    width: 10px;\n"
"    height: 10px;\n"
"    background: url(:/ScrollBar/ScrollBar/scrollbar_arrowdown_down.png);\n"
"}\n"
" \n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical \n"
""
                        "{\n"
"    background: none;\n"
"}"));
        verticalScrollBar->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalScrollBar);


        retranslateUi(temp);

        QMetaObject::connectSlotsByName(temp);
    } // setupUi

    void retranslateUi(QWidget *temp)
    {
        temp->setWindowTitle(QApplication::translate("temp", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class temp: public Ui_temp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMP_H
