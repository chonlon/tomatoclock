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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_temp
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_8;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_9;

    void setupUi(QWidget *temp)
    {
        if (temp->objectName().isEmpty())
            temp->setObjectName(QString::fromUtf8("temp"));
        temp->resize(638, 364);
        horizontalLayout = new QHBoxLayout(temp);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(temp);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 2, 3, 1, 2);

        pushButton_8 = new QPushButton(temp);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

        gridLayout->addWidget(pushButton_8, 0, 4, 1, 1);

        pushButton_3 = new QPushButton(temp);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 2, 1, 1, 1);

        pushButton_5 = new QPushButton(temp);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 0, 3, 1, 1);

        pushButton_2 = new QPushButton(temp);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_4 = new QPushButton(temp);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 2, 0, 1, 1);

        pushButton_6 = new QPushButton(temp);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 0, 0, 1, 1);

        pushButton_7 = new QPushButton(temp);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        gridLayout->addWidget(pushButton_7, 3, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        pushButton_9 = new QPushButton(temp);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setMinimumSize(QSize(45, 45));
        pushButton_9->setMaximumSize(QSize(45, 45));

        horizontalLayout->addWidget(pushButton_9);


        retranslateUi(temp);

        QMetaObject::connectSlotsByName(temp);
    } // setupUi

    void retranslateUi(QWidget *temp)
    {
        temp->setWindowTitle(QApplication::translate("temp", "Form", nullptr));
        pushButton->setText(QApplication::translate("temp", "PushButton", nullptr));
        pushButton_8->setText(QApplication::translate("temp", "PushButton", nullptr));
        pushButton_3->setText(QApplication::translate("temp", "PushButton", nullptr));
        pushButton_5->setText(QApplication::translate("temp", "PushButton", nullptr));
        pushButton_2->setText(QApplication::translate("temp", "PushButton", nullptr));
        pushButton_4->setText(QApplication::translate("temp", "PushButton", nullptr));
        pushButton_6->setText(QApplication::translate("temp", "PushButton", nullptr));
        pushButton_7->setText(QApplication::translate("temp", "PushButton", nullptr));
        pushButton_9->setText(QApplication::translate("temp", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class temp: public Ui_temp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMP_H
