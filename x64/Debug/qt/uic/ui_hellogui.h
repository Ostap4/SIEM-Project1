/********************************************************************************
** Form generated from reading UI file 'hellogui.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLOGUI_H
#define UI_HELLOGUI_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_helloguiClass
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *OpenLog;
    QPushButton *Export;
    QPushButton *Clear;
    QPushButton *Analyze;
    QTableWidget *tableWidget;
    QComboBox *comboBox_sortype;
    QLabel *label;
    QLabel *label_2;
    QComboBox *DateRange;
    QLabel *label_3;
    QLineEdit *lineIP_search;
    QPushButton *ApplySort;
    QLabel *label_4;
    QLineEdit *Username_search;
    QComboBox *comboBox_groupBy;
    QPushButton *RiskScoreDialog;
    QPushButton *TimeLine;
    QLabel *label_5;
    QPushButton *Correlation_Analyze;
    QPushButton *Load_Data_Base;
    QPushButton *TimeLog;
    QPushButton *LiveMode;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *helloguiClass)
    {
        if (helloguiClass->objectName().isEmpty())
            helloguiClass->setObjectName("helloguiClass");
        helloguiClass->resize(1097, 756);
        helloguiClass->setMaximumSize(QSize(1097, 16777215));
        helloguiClass->setAutoFillBackground(false);
        centralWidget = new QWidget(helloguiClass);
        centralWidget->setObjectName("centralWidget");
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(1, 2, 1091, 441));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        OpenLog = new QPushButton(layoutWidget);
        OpenLog->setObjectName("OpenLog");
        OpenLog->setLocale(QLocale(QLocale::English, QLocale::AmericanSamoa));

        gridLayout->addWidget(OpenLog, 0, 0, 1, 1);

        Export = new QPushButton(layoutWidget);
        Export->setObjectName("Export");

        gridLayout->addWidget(Export, 0, 2, 1, 1);

        Clear = new QPushButton(layoutWidget);
        Clear->setObjectName("Clear");

        gridLayout->addWidget(Clear, 0, 3, 1, 1);

        Analyze = new QPushButton(layoutWidget);
        Analyze->setObjectName("Analyze");
        Analyze->setEnabled(true);

        gridLayout->addWidget(Analyze, 0, 1, 1, 1);

        tableWidget = new QTableWidget(layoutWidget);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget->setObjectName("tableWidget");

        gridLayout->addWidget(tableWidget, 1, 0, 1, 4);

        comboBox_sortype = new QComboBox(centralWidget);
        comboBox_sortype->addItem(QString());
        comboBox_sortype->addItem(QString());
        comboBox_sortype->addItem(QString());
        comboBox_sortype->addItem(QString());
        comboBox_sortype->addItem(QString());
        comboBox_sortype->setObjectName("comboBox_sortype");
        comboBox_sortype->setGeometry(QRect(0, 470, 101, 22));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 445, 101, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 510, 61, 16));
        DateRange = new QComboBox(centralWidget);
        DateRange->addItem(QString());
        DateRange->addItem(QString());
        DateRange->addItem(QString());
        DateRange->setObjectName("DateRange");
        DateRange->setGeometry(QRect(0, 530, 91, 22));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 560, 49, 16));
        lineIP_search = new QLineEdit(centralWidget);
        lineIP_search->setObjectName("lineIP_search");
        lineIP_search->setGeometry(QRect(0, 580, 101, 21));
        ApplySort = new QPushButton(centralWidget);
        ApplySort->setObjectName("ApplySort");
        ApplySort->setGeometry(QRect(130, 570, 221, 41));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 620, 91, 16));
        Username_search = new QLineEdit(centralWidget);
        Username_search->setObjectName("Username_search");
        Username_search->setGeometry(QRect(0, 640, 101, 21));
        comboBox_groupBy = new QComboBox(centralWidget);
        comboBox_groupBy->addItem(QString());
        comboBox_groupBy->addItem(QString());
        comboBox_groupBy->addItem(QString());
        comboBox_groupBy->addItem(QString());
        comboBox_groupBy->setObjectName("comboBox_groupBy");
        comboBox_groupBy->setGeometry(QRect(0, 690, 111, 22));
        RiskScoreDialog = new QPushButton(centralWidget);
        RiskScoreDialog->setObjectName("RiskScoreDialog");
        RiskScoreDialog->setGeometry(QRect(410, 600, 221, 41));
        TimeLine = new QPushButton(centralWidget);
        TimeLine->setObjectName("TimeLine");
        TimeLine->setGeometry(QRect(410, 540, 221, 41));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 670, 91, 16));
        Correlation_Analyze = new QPushButton(centralWidget);
        Correlation_Analyze->setObjectName("Correlation_Analyze");
        Correlation_Analyze->setGeometry(QRect(410, 660, 221, 41));
        Load_Data_Base = new QPushButton(centralWidget);
        Load_Data_Base->setObjectName("Load_Data_Base");
        Load_Data_Base->setGeometry(QRect(410, 480, 221, 41));
        TimeLog = new QPushButton(centralWidget);
        TimeLog->setObjectName("TimeLog");
        TimeLog->setGeometry(QRect(130, 640, 221, 41));
        LiveMode = new QPushButton(centralWidget);
        LiveMode->setObjectName("LiveMode");
        LiveMode->setGeometry(QRect(130, 500, 221, 41));
        helloguiClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(helloguiClass);
        mainToolBar->setObjectName("mainToolBar");
        helloguiClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(helloguiClass);
        statusBar->setObjectName("statusBar");
        helloguiClass->setStatusBar(statusBar);

        retranslateUi(helloguiClass);

        QMetaObject::connectSlotsByName(helloguiClass);
    } // setupUi

    void retranslateUi(QMainWindow *helloguiClass)
    {
        helloguiClass->setWindowTitle(QCoreApplication::translate("helloguiClass", "hellogui", nullptr));
        OpenLog->setText(QCoreApplication::translate("helloguiClass", "OpenLog", nullptr));
        Export->setText(QCoreApplication::translate("helloguiClass", "Export", nullptr));
        Clear->setText(QCoreApplication::translate("helloguiClass", "Clear", nullptr));
        Analyze->setText(QCoreApplication::translate("helloguiClass", "Analyze", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("helloguiClass", " Timestamp \342\207\205", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("helloguiClass", "Source IP", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("helloguiClass", "Event Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("helloguiClass", "Serverity", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("helloguiClass", "Message", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("helloguiClass", "Username", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("helloguiClass", "Password", nullptr));
        comboBox_sortype->setItemText(0, QCoreApplication::translate("helloguiClass", "All", nullptr));
        comboBox_sortype->setItemText(1, QCoreApplication::translate("helloguiClass", "Info", nullptr));
        comboBox_sortype->setItemText(2, QCoreApplication::translate("helloguiClass", "Medium", nullptr));
        comboBox_sortype->setItemText(3, QCoreApplication::translate("helloguiClass", "High", nullptr));
        comboBox_sortype->setItemText(4, QCoreApplication::translate("helloguiClass", "Critical", nullptr));

        label->setText(QCoreApplication::translate("helloguiClass", "Serverity Sort", nullptr));
        label_2->setText(QCoreApplication::translate("helloguiClass", "Date range", nullptr));
        DateRange->setItemText(0, QCoreApplication::translate("helloguiClass", "All", nullptr));
        DateRange->setItemText(1, QCoreApplication::translate("helloguiClass", "Last 7 days", nullptr));
        DateRange->setItemText(2, QCoreApplication::translate("helloguiClass", "Last 30 days", nullptr));

        label_3->setText(QCoreApplication::translate("helloguiClass", "IP search", nullptr));
        ApplySort->setText(QCoreApplication::translate("helloguiClass", "ApplySort", nullptr));
        label_4->setText(QCoreApplication::translate("helloguiClass", "Username search", nullptr));
        comboBox_groupBy->setItemText(0, QCoreApplication::translate("helloguiClass", "Default", nullptr));
        comboBox_groupBy->setItemText(1, QCoreApplication::translate("helloguiClass", "Event Type", nullptr));
        comboBox_groupBy->setItemText(2, QCoreApplication::translate("helloguiClass", "Source IP", nullptr));
        comboBox_groupBy->setItemText(3, QCoreApplication::translate("helloguiClass", "Severity", nullptr));

        RiskScoreDialog->setText(QCoreApplication::translate("helloguiClass", "RiskScoreDialog", nullptr));
        TimeLine->setText(QCoreApplication::translate("helloguiClass", "Timeline", nullptr));
        label_5->setText(QCoreApplication::translate("helloguiClass", "Grouping By", nullptr));
        Correlation_Analyze->setText(QCoreApplication::translate("helloguiClass", "Correlation Analyze", nullptr));
        Load_Data_Base->setText(QCoreApplication::translate("helloguiClass", "Load DataBase", nullptr));
        TimeLog->setText(QCoreApplication::translate("helloguiClass", "Time Log", nullptr));
        LiveMode->setText(QCoreApplication::translate("helloguiClass", "STOP LIVE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class helloguiClass: public Ui_helloguiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLOGUI_H
