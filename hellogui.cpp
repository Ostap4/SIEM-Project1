#include "hellogui.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <Analyze.h> 
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <RiskScoreDialog.h>
#include <QMenu>
#include <QtCharts/QChartView> 
#include <QtCharts/QLineSeries> 
#include <QtCharts/QValueAxis> 
#include <CorrelationAnalyze.h>
#include <QSet>
#include <QDateTime>
#include <QtCharts/QDateTimeAxis>
#include <iostream>
#include <udplistener.h>
#include <QNetworkDatagram>
#include <QTimer>
#include <QUdpSocket>
#include <QHostAddress>
#include <AlertEngine.h>
#include "ReportGenerator.h"

//#include <TimeLine.h>


hellogui::hellogui(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle("SIEM Project");
 

    darkMode = true;
    applyTheme("dark.qss"); 
    ui.changeTheme->setText("☀ Light Mode");


    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid())
        db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("live.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Database error", db.lastError().text());
        return;
    }

    QSqlQuery q;
    if (!q.exec(R"(
    CREATE TABLE IF NOT EXISTS logs (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        timestamp TEXT,
        source_ip TEXT,
        event_type TEXT,
        severity TEXT,
        message TEXT,
        username TEXT,
        hash_password TEXT
    )
)")) {
        QMessageBox::critical(this, "Database error", q.lastError().text());
        return;
    }

    currentDbPath = "live.db";

    if (db.databaseName().endsWith("live.db")) {


        QSqlQuery qdel;
        if (!qdel.exec("DELETE FROM logs")) {
            qDebug() << "Failed to clear logs" << qdel.lastError().text();
        }

        if (!qdel.exec("DELETE FROM sqlite_sequence WHERE name='logs';")) {
        }
    }

    
    QHeaderView* header = ui.tableWidget->horizontalHeader();

    
    header->setSectionResizeMode(QHeaderView::Fixed);
    ui.tableWidget->setColumnWidth(0, 150);
    ui.tableWidget->setColumnWidth(4, 370);

    
    ui.tableWidget->setColumnWidth(1, 100);
    ui.tableWidget->setColumnWidth(2, 100);
    ui.tableWidget->setColumnWidth(3, 100);
    ui.tableWidget->setColumnWidth(5, 100);
    ui.tableWidget->setColumnWidth(6, 100);
   
    ui.lineIP_search->setPlaceholderText("IP search");
    ui.Username_search->setPlaceholderText("Enter username ");


    connect(ui.tableWidget->horizontalHeader(), &QHeaderView::sectionClicked, this, &hellogui::showSortTime);

    isLiveMode = true;             
    ui.LiveMode->setText("PAUSE LIVE"); 

    udpListener = new UdpListener(this);

    
    connect(udpListener, &UdpListener::logReceived, this, &hellogui::onUdpLogReceived);

    
    udpListener->startServer(5555);
    

    qDebug() << "SIEM is ready...";
   
}


hellogui::~hellogui(){ }



void hellogui::refresh_Table() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Błąd: Baza danych nie jest otwarta w refreshTable!";
        return;
    }

    ui.tableWidget->setRowCount(0);


    QSqlQuery query("SELECT id, timestamp, source_ip, event_type, severity, message, username, hash_password "
        "FROM logs ORDER BY timestamp ASC");

    if (query.lastError().isValid()) {
        qDebug() << "SQL SELECT error:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        ui.tableWidget->insertRow(row);

        // Timestamp
        QTableWidgetItem* timeItem = new QTableWidgetItem();
        QDateTime dt = QDateTime::fromString(query.value("timestamp").toString(), "yyyy-MM-dd HH:mm:ss");
        timeItem->setData(Qt::EditRole, dt);
        timeItem->setText(dt.toString("yyyy-MM-dd HH:mm:ss"));


        int id = query.value("id").toInt();
        timeItem->setData(Qt::UserRole, id);

        ui.tableWidget->setItem(row, 0, timeItem);


        ui.tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("source_ip").toString()));
        ui.tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("event_type").toString()));
        ui.tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("severity").toString()));
        ui.tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("message").toString()));
        ui.tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("username").toString()));
        ui.tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("hash_password").toString()));


        QString sev = query.value("severity").toString().trimmed().toLower();
        QColor bgColor;
        QColor textColor;


        if (darkMode) {
            if (sev == "critical") { bgColor = QColor("#ef4444"); textColor = Qt::white; }
            else if (sev == "high") { bgColor = QColor("#f59e0b"); textColor = Qt::white; }
            else if (sev == "medium") { bgColor = QColor("#fde047"); textColor = QColor("#111827"); }
            else { bgColor = QColor("#9ca3af"); textColor = QColor("#111827"); }
        }
        else {
            if (sev == "critical") { bgColor = QColor("#fecaca"); textColor = QColor("#111827"); }
            else if (sev == "high") { bgColor = QColor("#fed7aa"); textColor = QColor("#111827"); }
            else if (sev == "medium") { bgColor = QColor("#fef9c3"); textColor = QColor("#111827"); }
            else { bgColor = QColor("#f3f4f6"); textColor = QColor("#111827"); } 
        }

        QTableWidgetItem* severityItem = ui.tableWidget->item(row, 3);
        severityItem->setData(Qt::BackgroundRole, bgColor);
        severityItem->setData(Qt::ForegroundRole, textColor);
        severityItem->setTextAlignment(Qt::AlignCenter);
        

    }
    ui.tableWidget->viewport()->update();
}



void hellogui::on_OpenLog_clicked()
{
    table_layuot();
    ui.tableWidget->setRowCount(0);  

    ui.tableWidget->clear();
    ui.tableWidget->setColumnCount(7);


    ui.tableWidget->setHorizontalHeaderLabels(
        QStringList() << "Timestamp ⇅"
        << "Source IP"
        << "Event Type"
        << "Severity"
        << "Message"
        << "Username"
        << "Hash password");

    
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        if (!db.isValid())
            db = QSqlDatabase::addDatabase("QSQLITE");

        QString dbPath = currentDbPath.isEmpty() ? "log.db" : currentDbPath;
        db.setDatabaseName(dbPath);

        if (!db.open()) {
            QMessageBox::critical(this, "Database error", db.lastError().text());
            return;
        }
    }



    QSqlQuery selectIds("SELECT id FROM logs ORDER BY id ASC");
    QSqlQuery update;

    int counter = 1;
    while (selectIds.next()) {
        int id = selectIds.value(0).toInt();
        update.prepare("UPDATE logs SET username = ?, hash_password = ? WHERE id = ?");
        update.addBindValue(id);
        update.exec();

        counter++;
    }

    qDebug() << "Kolumny username i password_hash uzupełnione.";


    refresh_Table();
}


void hellogui::on_Analyze_clicked(){
   
    Analyze analyze;
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        QMessageBox::warning(this, "Error", "The database is not connected!");
        return;
    }

    db.transaction();

    QSqlQuery updateQuery;
   
    updateQuery.prepare("UPDATE logs SET event_type = :event_type, severity = :severity, message = :message "
        "WHERE id = :id");

    int updatedCount = 0;

    for (int row = 0; row < ui.tableWidget->rowCount(); ++row)
    {
       
        QTableWidgetItem* item = ui.tableWidget->item(row, 0);
        if (!item) {
            qDebug() << "Brak item w (row,0) dla wiersza:" << row;
            continue;
        }
        int id = item->data(Qt::UserRole).toInt();

        
        if (id == 0) {
            qDebug() << "Błąd: Brak ID dla wiersza " << row;
            continue;
        }

        QString fullLine = ui.tableWidget->item(row, 4)->text();

       
        QStringList splitline = fullLine.split(":");
        QString message = splitline.size() > 1 ? splitline.last().trimmed() : fullLine;

        QString eventType, severity;
        analyze.analyzeLine(fullLine, eventType, severity);
        
        updateQuery.bindValue(":event_type", eventType);
        updateQuery.bindValue(":severity", severity);
        updateQuery.bindValue(":message", message);
        updateQuery.bindValue(":id", id); 

        if (!updateQuery.exec()) {
            qDebug() << "Błąd SQL (ID=" << id << "):" << updateQuery.lastError().text();
        }
        else {
            updatedCount++;
        }
    }

    if (db.commit()) {
        QMessageBox::information(this, "Success", QString("%1 logs analyzed and updated.").arg(updatedCount));
        
        refresh_Table();
    }
    else {
        db.rollback();
        QMessageBox::critical(this, "Error", "Unable to save changes to the database.");
    }
}
   

void hellogui::on_Clear_clicked() {
    ui.tableWidget->setRowCount(0);
}

void hellogui::on_Export_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Export SIEM Report",
        "",
        "PDF Files (*.pdf)"
    );

    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive))
        fileName += ".pdf";

    bool ok = ReportGenerator::exportDashboardReport(ui.tableWidget, fileName);

    if (ok) {
        QMessageBox::information(this, "Export PDF", "SIEM analytical report exported successfully.");
    }
    else {
        QMessageBox::critical(this, "Export PDF", "Failed to export SIEM analytical report.");
    }
}



void hellogui::on_ApplySort_clicked()
{
    table_layuot();
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database error", "Database is not open.");
        return;
    }

    QString severity = ui.comboBox_sortype->currentText().trimmed();
    QString dateRange = ui.DateRange->currentText().trimmed();
    QString ip = ui.lineIP_search->text().trimmed();
    QString username = ui.Username_search->text().trimmed();
    QString groupBy = ui.comboBox_groupBy->currentText().trimmed();

    bool groupedMode = (groupBy != "Default");

    
    
    
    QStringList where;
    QList<QVariant> binds;

    if (severity != "All") {
        where << "severity = ?";
        binds << severity;
    }

    if (dateRange == "Last 7 days")
        where << "timestamp >= datetime('now', '-7 days')";
    else if (dateRange == "Last 30 days")
        where << "timestamp >= datetime('now', '-30 days')";

    if (!ip.isEmpty()) {
        where << "source_ip LIKE ?";
        binds << ("%" + ip + "%");
    }

    if (!username.isEmpty()) {
        where << "username LIKE ?";
        binds << ("%" + username + "%");
    }

    
   
   
    QString sql;
    
    if (!groupedMode) {
        sql =
            "SELECT timestamp, source_ip, event_type, severity, message, username, hash_password "
            "FROM logs ";
        if (!where.isEmpty())
            sql += "WHERE " + where.join(" AND ") + " ";
        sql += "ORDER BY timestamp DESC";
    }
    
    else {
        QString col;
        if (groupBy == "Event type")  col = "event_type";
        else if (groupBy == "Source IP") col = "source_ip";
        else if (groupBy == "Severity") col = "severity";
        else col = "event_type";

        sql =
            "SELECT " + col + " AS key_value, COUNT(*) AS cnt "
            "FROM logs ";
        if (!where.isEmpty())
            sql += "WHERE " + where.join(" AND ") + " ";
        sql += "GROUP BY " + col + " ORDER BY cnt DESC";
    }

   
    QSqlQuery query(db);
    query.prepare(sql);
    for (const QVariant& v : binds)
        query.addBindValue(v);

    if (!query.exec()) {
        QMessageBox::critical(this, "SQL error", query.lastError().text());
        qDebug() << sql;
        return;
    }

    
   

    if (!groupedMode) {
        ui.tableWidget->setColumnCount(7);
        ui.tableWidget->setHorizontalHeaderLabels({
            "Timestamp", "Source IP", "Event Type",
            "Severity", "Message", "Username", "Hash password"
            });

        ui.tableWidget->verticalHeader()->setVisible(true);
        ui.tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    }
    else {
        ui.tableWidget->setColumnCount(2);
        ui.tableWidget->setHorizontalHeaderLabels({ groupBy, "Count" });

        ui.tableWidget->verticalHeader()->setVisible(false);
        ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        ui.tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
        ui.tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    }

   
  
 
    int row = 0;

    if (!groupedMode) {
        while (query.next()) {
            ui.tableWidget->insertRow(row);

            ui.tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("timestamp").toString()));
            ui.tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("source_ip").toString()));
            ui.tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("event_type").toString()));
            ui.tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("severity").toString()));
            ui.tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("message").toString()));
            ui.tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("username").toString()));
            ui.tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("hash_password").toString()));

            QString sev = query.value("severity").toString().toLower();
            if (sev == "critical")
                ui.tableWidget->item(row, 3)->setBackground(Qt::red);
            else if (sev == "high")
                ui.tableWidget->item(row, 3)->setBackground(QColor(255, 165, 0));
            else if (sev == "medium") 
                ui.tableWidget->item(row, 3)->setBackground(Qt::yellow);
            else
                ui.tableWidget->item(row, 3)->setBackground(Qt::lightGray);

            row++;
        }
    }
    else {
        while (query.next()) {
            ui.tableWidget->insertRow(row);
            ui.tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("key_value").toString()));
            ui.tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("cnt").toString()));
            row++;
        }
    }

    if (row == 0)
        QMessageBox::information(this, "No results", "No logs match the selected filters.");
}


void hellogui::on_RiskScoreDialog_clicked() {

    RiskScoreDialog dlg(this);
    dlg.exec();

}

void hellogui::table_layuot()
{
   
    ui.tableWidget->clear();
    ui.tableWidget->setRowCount(0);
    ui.tableWidget->setColumnCount(7);

    ui.tableWidget->setHorizontalHeaderLabels({
        "Timestamp", "Source IP", "Event Type",
        "Severity", "Message", "Username", "Password" 
        });

    ui.tableWidget->setAlternatingRowColors(false);
    ui.tableWidget->verticalHeader()->setVisible(false);
    ui.tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    

    QHeaderView* header = ui.tableWidget->horizontalHeader();

   
    header->setSectionResizeMode(QHeaderView::Interactive);

   
    ui.tableWidget->setColumnWidth(0, 160);
    ui.tableWidget->setColumnWidth(1, 120);
    ui.tableWidget->setColumnWidth(2, 100);
    ui.tableWidget->setColumnWidth(3, 80);
    ui.tableWidget->setColumnWidth(4, 450);
    ui.tableWidget->setColumnWidth(5, 120);

   
    header->setSectionResizeMode(6, QHeaderView::Stretch);

   
    header->setStretchLastSection(false);
}

void hellogui::on_Correlation_Analyze_clicked()
{
    CorrelationAnalyzeDialog dlg(this);
    dlg.exec();
    
}


void hellogui::showSortTime(int column)
{
    if (column != 0)
        return;

    QMenu menu;

    QAction* ascending = menu.addAction("Ascending order");
    QAction* descending = menu.addAction("Descending order");

    QAction* selected = menu.exec(QCursor::pos());

    if (!selected)
        return;

    if (selected == ascending) {
        ui.tableWidget->sortItems(0, Qt::AscendingOrder);
        ui.tableWidget->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);

    }
    else if (selected == descending) {
        ui.tableWidget->sortItems(0, Qt::DescendingOrder);
        ui.tableWidget->horizontalHeader()->setSortIndicator(0, Qt::DescendingOrder);
    }

}

//void hellogui::on_TimeLine_clicked() {
//    TimeLine dlg(this);
//    dlg.exec();
//}

static bool validateLogDatabaseSchema(QWidget* parent)
{
    QSqlQuery query;

    if (!query.exec("PRAGMA table_info(logs);")) {
        QMessageBox::critical(
            parent,
            "Invalid database",
            "Table 'logs' does not exist."
        );
        return false;
    }

    QSet<QString> columns;
    while (query.next()) {
        columns.insert(query.value("name").toString());
    }

    QStringList requiredColumns = {
        "id",
        "source_ip",
        "timestamp",
        "event_type",
        "severity",
        "message",
        "username",
        "hash_password"
    };

    for (const QString& col : requiredColumns) {
        if (!columns.contains(col)) {
            QMessageBox::critical(
                parent,
                "Invalid database",
                "Database schema is not compatible.\nMissing column: " + col
            );
           

            return false;
        }
    }

    return true;
}




void hellogui::on_Load_Data_Base_clicked() {
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Load log database",
        "",
        "SQLite database (*.db)"
    );
    currentDbPath = filePath;

    if (filePath.isEmpty())
        return;

    QSqlDatabase db = QSqlDatabase::database();

    if (db.isOpen())
        db.close();

    db.setDatabaseName(filePath);

    if (!db.open()) {
        QMessageBox::critical(this, "Database error",
            "Failed to open selected database.");
        return;
    }

    if (!validateLogDatabaseSchema(this)) {
        db.close();
        return;
    }

    QMessageBox::information(
        this,
        "Database loaded",
        "Database loaded successfully.\nSchema is valid."
    );
    refresh_Table();
}


/*
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
----------------------------------------------------LIVE MODE--------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------
*/



void hellogui::showAlertNonBlocking(QMessageBox::Icon icon,
    const QString& title,
    const QString& text)
{
    auto* box = new QMessageBox(icon, title, text, QMessageBox::Ok, this);
    box->setAttribute(Qt::WA_DeleteOnClose);
    box->open();
}

void hellogui::on_changeTheme_clicked()
{
    toggleTheme();
}



void hellogui::processSecurityRules(QString ip, QString eventType, QString result) {
    result = result.trimmed();
    ip = ip.trimmed();


    //          DDoS                //

    securityEngine.trackEvent("DDOS_FLOOD", ip);

    if (securityEngine.shouldTrigger("DDOS_FLOOD", ip, 50, 3)) {
        qDebug() << "!!! ALARM DDOS !!!";
        QString msg = QString("🔥 CRITICAL NETWORK ALERT 🔥\n\n"
            "DDoS (Flood) attack detected!\n"
            "Source: %1\n"
            "Volume: >50 packets/3s").arg(ip);

        QApplication::beep(); // Dzwiek systemowy
        showAlertNonBlocking(QMessageBox::Critical, "NETWORK SECURITY ALERT", msg);
    
    }

    //              BRUTE-FORCE         //



    if (result == "FAILURE" || eventType.contains("Failure", Qt::CaseInsensitive)) {
        qDebug() << "DEBUG: Wykryto błąd logowania z IP:" << ip;

        
        securityEngine.trackEvent("BRUTE_FORCE", ip);

        
        if (securityEngine.shouldTrigger("BRUTE_FORCE", ip, 5, 60)) {

            
            qDebug() << "!!! ALARM BRUTE FORCE !!!";

            QString msg = QString("⚠️ SECURITY ALERT  ⚠️\n\n"
                "BRUTE-FORCE attack detected!\n"
                "IP address: %1\n"
                "Objective: Password cracking").arg(ip);

            QApplication::beep(); 
            showAlertNonBlocking(QMessageBox::Warning, "SECURITY ALERT", msg);
        }
    }
}




void hellogui::addLog(
    const QString& timestamp,
    const QString& ip,
    const QString& event,
    const QString& result,
    const QString& username,
    const QString& hash_password)

{

    QString severity;

    if (result == "SUCCESS") {
        severity = "INFO";
    }else {
        severity = "MEDIUM";
    
    }

    int row = ui.tableWidget->rowCount();
    ui.tableWidget->insertRow(row);
  
    QSqlQuery query;
    query.prepare(R"(
    INSERT INTO logs (timestamp, source_ip, event_type, message, severity, username, hash_password)
    VALUES (:ts, :ip, :ev, :mess, :sev, :user, :hash)
)");

    QString message;
    if (QString::compare(result.trimmed(), "SUCCESS", Qt::CaseInsensitive) == 0) {
        message = QString("Accepted password for %1 from %2").arg(username, ip);
        severity = "INFO";
    }
    else {
        message = QString("Failed password for %1 from %2").arg(username, ip);
        severity = "MEDIUM";
    }

    query.bindValue(":mess", message);
    query.bindValue(":ts", timestamp);
    query.bindValue(":ip", ip);
    query.bindValue(":ev", event);
    query.bindValue(":sev", severity);
    query.bindValue(":user", username);
    query.bindValue(":hash", hash_password);

    if (!query.exec()) {
        qDebug() << "INSERT failed:" << query.lastError().text();
        return; 
    }

    QVariant newId = query.lastInsertId();

    
    auto* tsItem = new QTableWidgetItem(timestamp);
    tsItem->setData(Qt::UserRole, newId);
    ui.tableWidget->setItem(row, 0, tsItem);

    ui.tableWidget->setItem(row, 1, new QTableWidgetItem(ip));
    ui.tableWidget->setItem(row, 2, new QTableWidgetItem(event));
    ui.tableWidget->setItem(row, 3, new QTableWidgetItem(severity));
    ui.tableWidget->setItem(row, 4, new QTableWidgetItem(message));
    ui.tableWidget->setItem(row, 5, new QTableWidgetItem(username));
    ui.tableWidget->setItem(row, 6, new QTableWidgetItem(hash_password));

    QTableWidgetItem* sevItem = new QTableWidgetItem(severity);
    ui.tableWidget->setItem(row, 3, sevItem);

    QString s = severity.toLower();
    QColor bgColor;
    QColor textColor;

    if (darkMode) {
        // DARK MODE
        if (s == "critical") { bgColor = Qt::red; textColor = Qt::white; }
        else if (s == "medium") { bgColor = Qt::yellow; textColor = Qt::black; }
        else { bgColor = Qt::lightGray; textColor = Qt::black; }
    }
    else {
        // LIGHT MODE
        if (s == "critical") { bgColor = QColor(255, 200, 200); textColor = Qt::black; }
        else if (s == "medium") { bgColor = QColor(255, 255, 200); textColor = Qt::black; }
        else { bgColor = Qt::white; textColor = Qt::black; }
    }

    sevItem->setBackground(bgColor);
    sevItem->setForeground(textColor);
    
 
    

}


void hellogui::on_TimeLog_clicked()
{
    addLog(
        QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"),
        "127.0.0.1",            
        "LOGIN",                    
        "SUCCESS",  
        "admin",            
        "hash"      
    );  
            
}


void hellogui::onUdpLogReceived(QString message, QString senderIp)
{
    qDebug() << "GUI RECEIVED UDP from" << senderIp << ":" << message;

    QStringList parts = message.split("|");

    if (parts.size() < 5) {
        qDebug() << "Invalid UDP log format:" << message;
        return;
    }

    if (!isLiveMode) {
        return;
    }

   
    QString ipFromLog = parts[0];   
    QString eventType = parts[1];   
    QString result = parts[2].trimmed();   
    QString username = parts[3];  
    QString hash = parts[4];   


    processSecurityRules(ipFromLog, eventType, result);

   
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    addLog(timestamp, ipFromLog, eventType, result, username, hash);

}


void hellogui::on_LiveMode_clicked() {
    isLiveMode = !isLiveMode;

    if (isLiveMode) {
        ui.LiveMode->setText("PAUSE LIVE");

        ui.statusBar->showMessage("Live Mode: ACTIVATED", 3000);

    } else {
        ui.LiveMode->setText("RESUME LIVE");

        ui.statusBar->showMessage("Live Mode: PAUSED", 3000);

    }

}

void hellogui::applyTheme(const QString& path)
{
    QFile file(path);
    qDebug() << "Trying to load theme from:" << path;
    qDebug() << "Exists?" << file.exists();

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "FAILED to open:" << file.errorString();
        return;
    }

    QTextStream stream(&file);
    const QString qss = stream.readAll();
    qDebug() << "Loaded QSS size:" << qss.size();

    qApp->setStyleSheet(qss);
    qDebug() << "Theme applied.";
}

void hellogui::toggleTheme()
{
    qDebug() << "Stary stan darkMode:" << darkMode;
    darkMode = !darkMode; 
    qDebug() << "Nowy stan darkMode:" << darkMode;

    if (darkMode) {
        
        applyTheme("dark.qss");
        ui.changeTheme->setText("☀ Light Mode");
        ui.statusBar->showMessage("Switched to Dark Mode", 2000);
    }
    else {
       
        applyTheme("light.qss");
        ui.changeTheme->setText("🌙 Dark Mode");
        ui.statusBar->showMessage("Switched to Light Mode", 2000);
    }

    
    refresh_Table();
}



