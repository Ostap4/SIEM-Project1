#include "CorrelationAnalyze.h"
#include "ui_correlation.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QMessageBox>



CorrelationAnalyzeDialog::CorrelationAnalyzeDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::CorrelationAnalyzeDialog)
{
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Error", "No connection to the database!\nMake sure that the main window has established a connection.");
    }

    ui->setupUi(this);

   
    setupComboBox();

    
    connect(ui->comboBox_correlation,
        QOverload<int>::of(&QComboBox::currentIndexChanged),
        this,
        &CorrelationAnalyzeDialog::onCorrelationTypeChanged);

    connect(ui->CorAnalyze,
        &QPushButton::clicked,
        this,
        &CorrelationAnalyzeDialog::onAnalyzeClicked);
    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sectionClicked,
        this, &CorrelationAnalyzeDialog::showSortMenu);

   
    onCorrelationTypeChanged(ui->comboBox_correlation->currentIndex());
}

CorrelationAnalyzeDialog::~CorrelationAnalyzeDialog()
{
    delete ui;
}


void CorrelationAnalyzeDialog::setupComboBox()
{
    ui->comboBox_correlation->clear();
    ui->comboBox_correlation->addItem("Failed → Success login");
    ui->comboBox_correlation->addItem("One IP → many endpoints");
}


void CorrelationAnalyzeDialog::onCorrelationTypeChanged(int index)
{
    configureTableForType(index);
}


void CorrelationAnalyzeDialog::configureTableForType(int index)
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    if (index == 0) {
        // Failed → Success
        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setHorizontalHeaderLabels({
            "IP",
            "Pattern",
            "Failed count ⇅",
            "Time range"
            });
        
        QHeaderView* header = ui->tableWidget->horizontalHeader();

        // Source IP
        header->setSectionResizeMode(0, QHeaderView::Interactive);
        ui->tableWidget->setColumnWidth(0, 100);

        // Pattern
        header->setSectionResizeMode(1, QHeaderView::Interactive);
        ui->tableWidget->setColumnWidth(1, 160);

        // Failed count
        header->setSectionResizeMode(2, QHeaderView::ResizeToContents);


        // Time range
        header->setSectionResizeMode(3, QHeaderView::Interactive);
        ui->tableWidget->setColumnWidth(3, 230);
    }
    else if (index == 1) {
        // One IP → many endpoints
        ui->tableWidget->setColumnCount(3);
        ui->tableWidget->setHorizontalHeaderLabels({
            "IP",
            "Endpoint count ⇅",
            "Attak Type"
            });
        
        QHeaderView* header = ui->tableWidget->horizontalHeader();

        // Source IP
        header->setSectionResizeMode(0, QHeaderView::Interactive);
        ui->tableWidget->setColumnWidth(0, 100);

        // Pattern
        header->setSectionResizeMode(1, QHeaderView::Interactive);
        ui->tableWidget->setColumnWidth(1, 160);
    }

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
   
}


void CorrelationAnalyzeDialog::onAnalyzeClicked()
{
    int type = ui->comboBox_correlation->currentIndex();
    ui->tableWidget->setRowCount(0);

    if (type == 0) {
        fillFailedSuccessTable();
    }
    else if (type == 1) {
        fillIpEndpointTable();
    }
    if (ui->tableWidget->rowCount() == 0) {
        QMessageBox::information(
            this,
            "Correlation Analyze",
            "No correlated events found for the selected criteria."
        );
    }
}


void CorrelationAnalyzeDialog::fillFailedSuccessTable()
{
    

    QSqlQuery query;
    QString sql = R"(
    SELECT 
        source_ip, 
        COUNT(*) AS failed_count, 
        MIN(timestamp) AS first_fail,
        MAX(timestamp) AS last_fail
    FROM logs 
    WHERE message LIKE 'Failed%' 
    GROUP BY source_ip 
    HAVING failed_count >= 3
)";


    if (!query.exec(sql)) {
        qDebug() << "SQL error:" << query.lastError().text();
        return;
    }

    int row = 0;

    while (query.next()) {
        QString ip = query.value("source_ip").toString();
        QString firstFail = query.value("first_fail").toString();
        QString lastFail = query.value("last_fail").toString();
        int failCount = query.value("failed_count").toInt();

        // SUCCESS po failach
        QSqlQuery success;
        success.prepare(R"(
            SELECT COUNT(*) 
            FROM logs 
            WHERE source_ip = :ip 
              AND message LIKE 'Accepted%' 
              AND timestamp >= :lastFail
        )");
        success.bindValue(":ip", ip);
        success.bindValue(":lastFail", lastFail);


        if (success.exec() && success.next() && success.value(0).toInt() > 0) {
            
               
                ui->tableWidget->insertRow(row);
                ui->tableWidget->setItem(row, 0, new QTableWidgetItem(ip));

               
                QTableWidgetItem* patternItem = new QTableWidgetItem("Brute-Force SUCCESS!");
                patternItem->setBackground(QColor(255, 100, 100));
                ui->tableWidget->setItem(row, 1, patternItem);

                ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(failCount)));
                ui->tableWidget->setItem(row, 3, new QTableWidgetItem(firstFail + " - " + lastFail));
                row++;
            
        }
    }
}


void CorrelationAnalyzeDialog::fillIpEndpointTable()
{
    QSqlQuery query;
    QString sql = R"(
        SELECT 
            source_ip, 
            COUNT(DISTINCT username) AS unique_users
        FROM logs 
        WHERE message LIKE 'Failed%'
        GROUP BY source_ip 
        HAVING unique_users >= 3
    )";

    if (!query.exec(sql)) {
        qDebug() << "SQL error:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->tableWidget->insertRow(row);

        QString ip = query.value("source_ip").toString();
        QString count = query.value("unique_users").toString();

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(ip));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(count));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem("User Enumeration Attack"));

        row++;
    }
}

void CorrelationAnalyzeDialog::showSortMenu(int column)
{

    QMenu menu;

    QAction* asacending = menu.addAction("Descending order");
    QAction* descending = menu.addAction("Ascending order");

    QAction* selected = menu.exec(QCursor::pos());

    if (!selected)
        return;

    if (selected == asacending) {
        ui->tableWidget->sortItems(column, Qt::AscendingOrder);
        ui->tableWidget->horizontalHeader()->setSortIndicator(column, Qt::AscendingOrder);

    }
    else if (selected == descending) {
        ui->tableWidget->sortItems(column, Qt::DescendingOrder);
        ui->tableWidget->horizontalHeader()->setSortIndicator(column, Qt::DescendingOrder);
    }

}
