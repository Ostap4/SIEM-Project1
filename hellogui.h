#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_hellogui.h"
#include "udplistener.h"
#include "AlertEngine.h"
#include <QMessageBox>
class hellogui : public QMainWindow
{
    Q_OBJECT

public:
    hellogui(QWidget *parent = nullptr);
    ~hellogui();

    

private slots:
    void on_OpenLog_clicked();
    void on_Analyze_clicked();
    void on_Clear_clicked();
    void on_Export_clicked();
    void on_ApplySort_clicked();
    void on_RiskScoreDialog_clicked();
    void table_layuot();
    void on_Correlation_Analyze_clicked();
    void on_Load_Data_Base_clicked();
    void addLog(const QString& timestamp, const QString& source_ip, const QString& event, const QString& result, const QString& username, const QString& hash_password);
    void refresh_Table();
    void on_TimeLog_clicked();

    void onUdpLogReceived(QString message, QString senderIp);
    void on_LiveMode_clicked();
    void showAlertNonBlocking(QMessageBox::Icon icon, const QString& title, const QString& text);

    
    
    //void on_TimeLine_clicked();
   
private:
    Ui::helloguiClass ui;;
    void showSortTime(int column);
    
    QString currentDbPath;

    UdpListener* udpListener = nullptr;
    bool isLiveMode = false;

    AlertEngine securityEngine;
    void processSecurityRules(QString ip, QString eventType, QString result);
   

   


};

