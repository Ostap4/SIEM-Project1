#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QMenu>
#include <QAction>
#include <QPoint>
#include "RiskScoreDialog.h"
#include "ui_riskscoredialog.h"



RiskScoreDialog::RiskScoreDialog(QWidget* parent)
	:QDialog(parent)
	, ui(new Ui::RiskScoreDialog)

{


	ui->setupUi(this);
	setWindowTitle("Risk Score Ranking");
	loadRiskScore();
	connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sectionClicked,
		this, &RiskScoreDialog::showSortMenu);


}



RiskScoreDialog::~RiskScoreDialog() {

	delete ui;
}

void RiskScoreDialog::loadRiskScore()
{
	
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({ "Source IP", "Risk Score", "Failed (1 min)", "Total Fails" });

    QSqlQuery query;

    QString sql = R"(
        SELECT 
            source_ip, 
            SUM(CASE severity 
                WHEN 'Critical' THEN 10 
                WHEN 'High' THEN 5 
                WHEN 'Medium' THEN 3 
                WHEN 'Info' THEN 0 
                ELSE 1 END) AS risk_score,
            
            SUM(CASE 
                WHEN (message LIKE 'Failed%' OR severity = 'MEDIUM') 
                     AND timestamp >= datetime('now', 'localtime', '-1 minute') 
                THEN 1 ELSE 0 END) AS recent_fails,

            SUM(CASE 
                WHEN (message LIKE 'Failed%' OR severity = 'MEDIUM') 
                THEN 1 ELSE 0 END) AS total_fails

        FROM logs 
        GROUP BY source_ip 
        ORDER BY risk_score DESC
    )";

    if (!query.exec(sql)) {
        qDebug() << "SQL error:" << query.lastError().text();
        return;
    }

    int row = 0;
    ui->tableWidget->setSortingEnabled(false); 

    while (query.next()) {
        ui->tableWidget->insertRow(row);

        QString ip = query.value(0).toString();
        int risk = query.value(1).toInt();
        int failsRecent = query.value(2).toInt();
        int failsTotal = query.value(3).toInt();

        // 0. Source IP
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(ip));

        // 1. Risk Score
        QTableWidgetItem* riskItem = new QTableWidgetItem();
        riskItem->setData(Qt::EditRole, risk);
        ui->tableWidget->setItem(row, 1, riskItem);

        // 2. Failed 1 min 
        QTableWidgetItem* failItem = new QTableWidgetItem();
        failItem->setData(Qt::EditRole, failsRecent);
        ui->tableWidget->setItem(row, 2, failItem);

        // 3. Total Fails 
        QTableWidgetItem* totalItem = new QTableWidgetItem();
        totalItem->setData(Qt::EditRole, failsTotal);
        ui->tableWidget->setItem(row, 3, totalItem);

        
        // Risk Score
        if (risk >= 50)       riskItem->setBackground(QColor(255, 80, 80));  
        else if (risk >= 20)  riskItem->setBackground(QColor(255, 160, 60)); 
        else if (risk > 0)    riskItem->setBackground(QColor(255, 255, 200)); 

        
        if (failsRecent >= 5) {
            failItem->setBackground(Qt::red);
            failItem->setForeground(Qt::white);
        }

        row++;
    }

    ui->tableWidget->setSortingEnabled(true); 

    
    QHeaderView* header = ui->tableWidget->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::Stretch);
    header->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents);
}



void RiskScoreDialog::showSortMenu(int column)
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




