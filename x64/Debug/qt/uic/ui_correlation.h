/********************************************************************************
** Form generated from reading UI file 'correlation.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CORRELATION_H
#define UI_CORRELATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_CorrelationAnalyzeDialog
{
public:
    QTableWidget *tableWidget;
    QLabel *label_6;
    QComboBox *comboBox_correlation;
    QPushButton *CorAnalyze;

    void setupUi(QDialog *CorrelationAnalyzeDialog)
    {
        if (CorrelationAnalyzeDialog->objectName().isEmpty())
            CorrelationAnalyzeDialog->setObjectName("CorrelationAnalyzeDialog");
        CorrelationAnalyzeDialog->resize(835, 355);
        tableWidget = new QTableWidget(CorrelationAnalyzeDialog);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 10, 621, 321));
        label_6 = new QLabel(CorrelationAnalyzeDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(630, 10, 91, 16));
        comboBox_correlation = new QComboBox(CorrelationAnalyzeDialog);
        comboBox_correlation->addItem(QString());
        comboBox_correlation->addItem(QString());
        comboBox_correlation->addItem(QString());
        comboBox_correlation->setObjectName("comboBox_correlation");
        comboBox_correlation->setGeometry(QRect(630, 30, 151, 22));
        CorAnalyze = new QPushButton(CorrelationAnalyzeDialog);
        CorAnalyze->setObjectName("CorAnalyze");
        CorAnalyze->setGeometry(QRect(630, 60, 111, 21));

        retranslateUi(CorrelationAnalyzeDialog);

        QMetaObject::connectSlotsByName(CorrelationAnalyzeDialog);
    } // setupUi

    void retranslateUi(QDialog *CorrelationAnalyzeDialog)
    {
        CorrelationAnalyzeDialog->setWindowTitle(QCoreApplication::translate("CorrelationAnalyzeDialog", "Dialog", nullptr));
        label_6->setText(QCoreApplication::translate("CorrelationAnalyzeDialog", "Correlation type", nullptr));
        comboBox_correlation->setItemText(0, QCoreApplication::translate("CorrelationAnalyzeDialog", "None", nullptr));
        comboBox_correlation->setItemText(1, QCoreApplication::translate("CorrelationAnalyzeDialog", "Failed -> Success", nullptr));
        comboBox_correlation->setItemText(2, QCoreApplication::translate("CorrelationAnalyzeDialog", "One IP -> many endpoints", nullptr));

        CorAnalyze->setText(QCoreApplication::translate("CorrelationAnalyzeDialog", "Analyze", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CorrelationAnalyzeDialog: public Ui_CorrelationAnalyzeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CORRELATION_H
