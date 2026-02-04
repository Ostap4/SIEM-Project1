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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_helloguiClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QFrame *sidebar;
    QVBoxLayout *verticalLayout;
    QGroupBox *filters;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_5;
    QComboBox *comboBox_sortype;
    QComboBox *comboBox_groupBy;
    QLabel *label_2;
    QComboBox *DateRange;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *Username_search;
    QLineEdit *lineIP_search;
    QPushButton *ApplySort;
    QGroupBox *buttons;
    QFormLayout *formLayout_2;
    QPushButton *Correlation_Analyze;
    QPushButton *Load_Data_Base;
    QPushButton *TimeLog;
    QPushButton *TimeLine;
    QPushButton *RiskScoreDialog;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QFrame *kontent;
    QVBoxLayout *verticalLayout_2;
    QFrame *topbar;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *LiveMode;
    QPushButton *Analyze;
    QPushButton *OpenLog;
    QPushButton *Export;
    QPushButton *Clear;
    QPushButton *changeTheme;
    QSpacerItem *horizontalSpacer_3;
    QLabel *h1;
    QTableWidget *tableWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *helloguiClass)
    {
        if (helloguiClass->objectName().isEmpty())
            helloguiClass->setObjectName("helloguiClass");
        helloguiClass->resize(1489, 1500);
        helloguiClass->setMinimumSize(QSize(0, 0));
        helloguiClass->setMaximumSize(QSize(16777215, 16777215));
        helloguiClass->setAutoFillBackground(false);
        centralWidget = new QWidget(helloguiClass);
        centralWidget->setObjectName("centralWidget");
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        sidebar = new QFrame(centralWidget);
        sidebar->setObjectName("sidebar");
        sidebar->setMinimumSize(QSize(260, 0));
        sidebar->setMaximumSize(QSize(320, 16777215));
        sidebar->setFrameShape(QFrame::StyledPanel);
        sidebar->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(sidebar);
        verticalLayout->setSpacing(10);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(12, 12, 12, 12);
        filters = new QGroupBox(sidebar);
        filters->setObjectName("filters");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(filters->sizePolicy().hasHeightForWidth());
        filters->setSizePolicy(sizePolicy);
        filters->setMinimumSize(QSize(300, 300));
        filters->setMaximumSize(QSize(320, 500));
        formLayout = new QFormLayout(filters);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName("formLayout");
        label = new QLabel(filters);
        label->setObjectName("label");
        label->setMaximumSize(QSize(16777215, 20));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_5 = new QLabel(filters);
        label_5->setObjectName("label_5");
        label_5->setMaximumSize(QSize(80, 20));

        formLayout->setWidget(0, QFormLayout::FieldRole, label_5);

        comboBox_sortype = new QComboBox(filters);
        comboBox_sortype->addItem(QString());
        comboBox_sortype->addItem(QString());
        comboBox_sortype->addItem(QString());
        comboBox_sortype->addItem(QString());
        comboBox_sortype->addItem(QString());
        comboBox_sortype->setObjectName("comboBox_sortype");
        comboBox_sortype->setMaximumSize(QSize(80, 16777215));

        formLayout->setWidget(1, QFormLayout::LabelRole, comboBox_sortype);

        comboBox_groupBy = new QComboBox(filters);
        comboBox_groupBy->addItem(QString());
        comboBox_groupBy->addItem(QString());
        comboBox_groupBy->addItem(QString());
        comboBox_groupBy->addItem(QString());
        comboBox_groupBy->setObjectName("comboBox_groupBy");
        comboBox_groupBy->setMaximumSize(QSize(80, 16777215));

        formLayout->setWidget(1, QFormLayout::FieldRole, comboBox_groupBy);

        label_2 = new QLabel(filters);
        label_2->setObjectName("label_2");
        label_2->setMaximumSize(QSize(80, 20));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        DateRange = new QComboBox(filters);
        DateRange->addItem(QString());
        DateRange->addItem(QString());
        DateRange->addItem(QString());
        DateRange->setObjectName("DateRange");
        DateRange->setMaximumSize(QSize(80, 16777215));

        formLayout->setWidget(3, QFormLayout::LabelRole, DateRange);

        label_4 = new QLabel(filters);
        label_4->setObjectName("label_4");
        label_4->setMaximumSize(QSize(16777215, 20));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        label_3 = new QLabel(filters);
        label_3->setObjectName("label_3");
        label_3->setMaximumSize(QSize(16777215, 20));

        formLayout->setWidget(4, QFormLayout::FieldRole, label_3);

        Username_search = new QLineEdit(filters);
        Username_search->setObjectName("Username_search");
        Username_search->setMaximumSize(QSize(130, 16777215));

        formLayout->setWidget(5, QFormLayout::LabelRole, Username_search);

        lineIP_search = new QLineEdit(filters);
        lineIP_search->setObjectName("lineIP_search");
        lineIP_search->setMaximumSize(QSize(130, 16777215));

        formLayout->setWidget(5, QFormLayout::FieldRole, lineIP_search);

        ApplySort = new QPushButton(filters);
        ApplySort->setObjectName("ApplySort");
        ApplySort->setMinimumSize(QSize(270, 30));
        ApplySort->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(6, QFormLayout::SpanningRole, ApplySort);


        verticalLayout->addWidget(filters);

        buttons = new QGroupBox(sidebar);
        buttons->setObjectName("buttons");
        buttons->setMinimumSize(QSize(300, 200));
        buttons->setMaximumSize(QSize(320, 16777215));
        formLayout_2 = new QFormLayout(buttons);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName("formLayout_2");
        Correlation_Analyze = new QPushButton(buttons);
        Correlation_Analyze->setObjectName("Correlation_Analyze");
        Correlation_Analyze->setMaximumSize(QSize(150, 16777215));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, Correlation_Analyze);

        Load_Data_Base = new QPushButton(buttons);
        Load_Data_Base->setObjectName("Load_Data_Base");
        Load_Data_Base->setMaximumSize(QSize(150, 16777215));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, Load_Data_Base);

        TimeLog = new QPushButton(buttons);
        TimeLog->setObjectName("TimeLog");
        TimeLog->setMaximumSize(QSize(150, 16777215));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, TimeLog);

        TimeLine = new QPushButton(buttons);
        TimeLine->setObjectName("TimeLine");
        TimeLine->setMaximumSize(QSize(150, 16777215));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, TimeLine);

        RiskScoreDialog = new QPushButton(buttons);
        RiskScoreDialog->setObjectName("RiskScoreDialog");
        RiskScoreDialog->setMaximumSize(QSize(150, 16777215));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, RiskScoreDialog);


        verticalLayout->addWidget(buttons);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addWidget(sidebar);

        verticalSpacer = new QSpacerItem(20, 1446, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout->addItem(verticalSpacer);

        kontent = new QFrame(centralWidget);
        kontent->setObjectName("kontent");
        sizePolicy.setHeightForWidth(kontent->sizePolicy().hasHeightForWidth());
        kontent->setSizePolicy(sizePolicy);
        kontent->setFrameShape(QFrame::StyledPanel);
        kontent->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(kontent);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        topbar = new QFrame(kontent);
        topbar->setObjectName("topbar");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(topbar->sizePolicy().hasHeightForWidth());
        topbar->setSizePolicy(sizePolicy1);
        topbar->setMinimumSize(QSize(0, 44));
        topbar->setMaximumSize(QSize(16777215, 60));
        topbar->setFrameShape(QFrame::StyledPanel);
        topbar->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(topbar);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        LiveMode = new QPushButton(topbar);
        LiveMode->setObjectName("LiveMode");

        horizontalLayout_2->addWidget(LiveMode);

        Analyze = new QPushButton(topbar);
        Analyze->setObjectName("Analyze");
        Analyze->setEnabled(true);

        horizontalLayout_2->addWidget(Analyze);

        OpenLog = new QPushButton(topbar);
        OpenLog->setObjectName("OpenLog");
        OpenLog->setLocale(QLocale(QLocale::English, QLocale::AmericanSamoa));

        horizontalLayout_2->addWidget(OpenLog);

        Export = new QPushButton(topbar);
        Export->setObjectName("Export");

        horizontalLayout_2->addWidget(Export);

        Clear = new QPushButton(topbar);
        Clear->setObjectName("Clear");

        horizontalLayout_2->addWidget(Clear);

        changeTheme = new QPushButton(topbar);
        changeTheme->setObjectName("changeTheme");

        horizontalLayout_2->addWidget(changeTheme);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_2->addWidget(topbar);

        h1 = new QLabel(kontent);
        h1->setObjectName("h1");
        h1->setMaximumSize(QSize(100, 16777215));

        verticalLayout_2->addWidget(h1);

        tableWidget = new QTableWidget(kontent);
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
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setMinimumSize(QSize(0, 0));

        verticalLayout_2->addWidget(tableWidget);


        horizontalLayout->addWidget(kontent);

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
        filters->setTitle(QCoreApplication::translate("helloguiClass", "Filters", nullptr));
        label->setText(QCoreApplication::translate("helloguiClass", "Serverity Sort", nullptr));
        label_5->setText(QCoreApplication::translate("helloguiClass", "Grouping By", nullptr));
        comboBox_sortype->setItemText(0, QCoreApplication::translate("helloguiClass", "All", nullptr));
        comboBox_sortype->setItemText(1, QCoreApplication::translate("helloguiClass", "Info", nullptr));
        comboBox_sortype->setItemText(2, QCoreApplication::translate("helloguiClass", "Medium", nullptr));
        comboBox_sortype->setItemText(3, QCoreApplication::translate("helloguiClass", "High", nullptr));
        comboBox_sortype->setItemText(4, QCoreApplication::translate("helloguiClass", "Critical", nullptr));

        comboBox_groupBy->setItemText(0, QCoreApplication::translate("helloguiClass", "Default", nullptr));
        comboBox_groupBy->setItemText(1, QCoreApplication::translate("helloguiClass", "Event Type", nullptr));
        comboBox_groupBy->setItemText(2, QCoreApplication::translate("helloguiClass", "Source IP", nullptr));
        comboBox_groupBy->setItemText(3, QCoreApplication::translate("helloguiClass", "Severity", nullptr));

        label_2->setText(QCoreApplication::translate("helloguiClass", "Date range", nullptr));
        DateRange->setItemText(0, QCoreApplication::translate("helloguiClass", "All", nullptr));
        DateRange->setItemText(1, QCoreApplication::translate("helloguiClass", "Last 7 days", nullptr));
        DateRange->setItemText(2, QCoreApplication::translate("helloguiClass", "Last 30 days", nullptr));

        label_4->setText(QCoreApplication::translate("helloguiClass", "Username search", nullptr));
        label_3->setText(QCoreApplication::translate("helloguiClass", "IP search", nullptr));
        ApplySort->setText(QCoreApplication::translate("helloguiClass", "ApplySort", nullptr));
        buttons->setTitle(QString());
        Correlation_Analyze->setText(QCoreApplication::translate("helloguiClass", "Correlation Analyze", nullptr));
        Load_Data_Base->setText(QCoreApplication::translate("helloguiClass", "Load DataBase", nullptr));
        TimeLog->setText(QCoreApplication::translate("helloguiClass", "Time Log", nullptr));
        TimeLine->setText(QCoreApplication::translate("helloguiClass", "Timeline", nullptr));
        RiskScoreDialog->setText(QCoreApplication::translate("helloguiClass", "RiskScoreDialog", nullptr));
        LiveMode->setText(QCoreApplication::translate("helloguiClass", "STOP LIVE", nullptr));
        Analyze->setText(QCoreApplication::translate("helloguiClass", "Analyze", nullptr));
        OpenLog->setText(QCoreApplication::translate("helloguiClass", "OpenLog", nullptr));
        Export->setText(QCoreApplication::translate("helloguiClass", "Export", nullptr));
        Clear->setText(QCoreApplication::translate("helloguiClass", "Clear", nullptr));
        changeTheme->setText(QCoreApplication::translate("helloguiClass", "Change Theme", nullptr));
        h1->setText(QCoreApplication::translate("helloguiClass", "Log Events:", nullptr));
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
    } // retranslateUi

};

namespace Ui {
    class helloguiClass: public Ui_helloguiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLOGUI_H
