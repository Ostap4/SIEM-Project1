#pragma once

#include <QString>
#include <QTableWidget>

class ReportGenerator
{
public:
    static bool exportDashboardReport(QTableWidget* tableWidget, const QString& fileName);

private:
    static QString buildReportHtml(QTableWidget* tableWidget);
    static QString buildMetadataHtml();
    static QString buildSummaryHtml(QTableWidget* tableWidget);
    static QString buildLogsTableHtml(QTableWidget* tableWidget);

    static QString getCellText(QTableWidget* tableWidget, int row, int col);
    static int findColumnByName(QTableWidget* tableWidget, const QString& name);
};