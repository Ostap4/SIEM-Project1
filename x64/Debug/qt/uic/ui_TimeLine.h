/********************************************************************************
** Form generated from reading UI file 'TimeLine.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMELINE_H
#define UI_TIMELINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeLine
{
public:
    QWidget *charWidget;

    void setupUi(QDialog *TimeLine)
    {
        if (TimeLine->objectName().isEmpty())
            TimeLine->setObjectName("TimeLine");
        TimeLine->resize(400, 300);
        charWidget = new QWidget(TimeLine);
        charWidget->setObjectName("charWidget");
        charWidget->setGeometry(QRect(20, 20, 351, 251));

        retranslateUi(TimeLine);

        QMetaObject::connectSlotsByName(TimeLine);
    } // setupUi

    void retranslateUi(QDialog *TimeLine)
    {
        TimeLine->setWindowTitle(QCoreApplication::translate("TimeLine", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimeLine: public Ui_TimeLine {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMELINE_H
