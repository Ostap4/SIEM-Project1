/********************************************************************************
** Form generated from reading UI file 'riskscoredialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RISKSCOREDIALOG_H
#define UI_RISKSCOREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_RiskScoreDialog
{
public:
    QTableWidget *tableWidget;

    void setupUi(QDialog *RiskScoreDialog)
    {
        if (RiskScoreDialog->objectName().isEmpty())
            RiskScoreDialog->setObjectName("RiskScoreDialog");
        RiskScoreDialog->resize(590, 350);
        tableWidget = new QTableWidget(RiskScoreDialog);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QFont font;
        font.setPointSize(9);
        font.setBold(false);
        font.setItalic(false);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(20, 10, 421, 301));

        retranslateUi(RiskScoreDialog);

        QMetaObject::connectSlotsByName(RiskScoreDialog);
    } // setupUi

    void retranslateUi(QDialog *RiskScoreDialog)
    {
        RiskScoreDialog->setWindowTitle(QCoreApplication::translate("RiskScoreDialog", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("RiskScoreDialog", "Source IP", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("RiskScoreDialog", "Risk Score", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("RiskScoreDialog", "Failed (1 minute)", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("RiskScoreDialog", "Total Fails", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RiskScoreDialog: public Ui_RiskScoreDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RISKSCOREDIALOG_H
