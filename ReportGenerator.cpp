
#include "ReportGenerator.h"
#include <QTextDocument>
#include <QPrinter>
#include <QPageLayout>
#include <QDateTime>
#include <QMap>
#include <QTableWidgetItem>
#include <QDebug>
#include <QMessageBox>

bool ReportGenerator::exportDashboardReport(QTableWidget* tableWidget, const QString& fileName)
{
    if (!tableWidget)
        return false;

    QTextDocument doc;
    doc.setHtml(buildReportHtml(tableWidget));

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageOrientation(QPageLayout::Landscape);

    doc.print(&printer);

    return true;
}

QString ReportGenerator::buildReportHtml(QTableWidget* tableWidget)
{
    QString html;

    html += R"(
    <html>
    <head>
        <meta charset="utf-8">
        <style>
            body { font-family: Arial, sans-serif; font-size: 9pt; color: #222; }
            h1 { font-size: 18pt; border-bottom: 2px solid #333; padding-bottom: 6px; }
            h2 { margin-top: 22px; font-size: 13pt; border-bottom: 1px solid #999; padding-bottom: 4px; }
            table { width: 100%; border-collapse: collapse; table-layout: fixed; margin-top: 8px; }
            th, td { border: 1px solid #444; padding: 4px; vertical-align: top; word-wrap: break-word; }
            th { background: #222831; color: white; }
            .critical { background-color: #b00020; color: white; font-weight: bold; }
            .high { background-color: #ff6d00; color: white; font-weight: bold; }
            .medium { background-color: #ffd54f; color: black; font-weight: bold; }
            .info { background-color: #64b5f6; color: black; font-weight: bold; }
            .recommendation { margin-top: 10px; padding: 8px; border: 1px solid #999; background: #f2f2f2; }
        </style>
    </head>
    <body>
    )";

    html += "<h1>Real-Time SIEM Simulator — Analytical Report</h1>";
    html += buildMetadataHtml();
    html += buildSummaryHtml(tableWidget);
    html += buildLogsTableHtml(tableWidget);
    html += "</body></html>";

    return html;
}

QString ReportGenerator::buildMetadataHtml()
{
    QString html;

    html += "<h2>1. Report metadata</h2>";
    html += "<table>";
    html += "<tr><td><b>Generated at</b></td><td>" +
        QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss").toHtmlEscaped() +
        "</td></tr>";
    html += "<tr><td><b>Source</b></td><td>Current dashboard filtered table</td></tr>";
    html += "</table>";

    return html;
}

QString ReportGenerator::getCellText(QTableWidget* tableWidget, int row, int col)
{
    QTableWidgetItem* item = tableWidget->item(row, col);
    return item ? item->text() : "";
}

int ReportGenerator::findColumnByName(QTableWidget* tableWidget, const QString& name)
{
    for (int col = 0; col < tableWidget->columnCount(); ++col) {
        QTableWidgetItem* header = tableWidget->horizontalHeaderItem(col);

        if (!header)
            continue;

        if (header->text().contains(name, Qt::CaseInsensitive))
            return col;
    }

    return -1;
}

QString ReportGenerator::buildSummaryHtml(QTableWidget* tableWidget)
{
    int severityCol = findColumnByName(tableWidget, "Serverity");
    int ipCol = findColumnByName(tableWidget, "IP");
    int usernameCol = findColumnByName(tableWidget, "Username");

    int total = 0;
    int critical = 0;
    int high = 0;
    int medium = 0;
    int info = 0;

    QMap<QString, int> ipCounter;
    QMap<QString, int> userCounter;

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        if (tableWidget->isRowHidden(row))
            continue;

        total++;

        QString severity = severityCol >= 0 ? getCellText(tableWidget, row, severityCol).trimmed().toLower() : "";

        if (severity == "critical")
            critical++;
        else if (severity == "high")
            high++;
        else if (severity == "medium")
            medium++;
        else
            info++;

        if (ipCol >= 0) {
            QString ip = getCellText(tableWidget, row, ipCol);
            if (!ip.isEmpty())
                ipCounter[ip]++;
        }

        if (usernameCol >= 0) {
            QString username = getCellText(tableWidget, row, usernameCol);
            if (!username.isEmpty())
                userCounter[username]++;
        }
    }

    QString mostCommonIp = "-";
    int maxIp = 0;

    for (auto it = ipCounter.begin(); it != ipCounter.end(); ++it) {
        if (it.value() > maxIp) {
            maxIp = it.value();
            mostCommonIp = it.key();
        }
    }

    QString mostCommonUser = "-";
    int maxUser = 0;

    for (auto it = userCounter.begin(); it != userCounter.end(); ++it) {
        if (it.value() > maxUser) {
            maxUser = it.value();
            mostCommonUser = it.key();
        }
    }

    QString recommendation;

    if (critical > 0 || high >= 5) {
        recommendation = "Escalation recommended. Critical or multiple high severity events were detected.";
    }
    else if (medium >= 10) {
        recommendation = "Monitoring recommended. Multiple medium severity events were detected.";
    }
    else {
        recommendation = "No immediate escalation required based on the current filtered dataset.";
    }

    QString html;

    html += "<h2>2. Summary</h2>";
    html += "<table>";
    html += "<tr><td><b>Total logs</b></td><td>" + QString::number(total) + "</td></tr>";
    html += "<tr><td><b>Critical</b></td><td>" + QString::number(critical) + "</td></tr>";
    html += "<tr><td><b>High</b></td><td>" + QString::number(high) + "</td></tr>";
    html += "<tr><td><b>Medium</b></td><td>" + QString::number(medium) + "</td></tr>";
    html += "<tr><td><b>Info / Low / Other</b></td><td>" + QString::number(info) + "</td></tr>";
    html += "<tr><td><b>Most common IP</b></td><td>" + mostCommonIp.toHtmlEscaped() + "</td></tr>";
    html += "<tr><td><b>Most common user</b></td><td>" + mostCommonUser.toHtmlEscaped() + "</td></tr>";
    html += "</table>";

    html += "<div class='recommendation'><b>Recommendation:</b><br>";
    html += recommendation.toHtmlEscaped();
    html += "</div>";

    return html;
}

QString ReportGenerator::buildLogsTableHtml(QTableWidget* tableWidget)
{
    QVector<int> visibleCols;
    int severityCol = -1;

    for (int col = 0; col < tableWidget->columnCount(); ++col) {
        if (tableWidget->isColumnHidden(col))
            continue;

        visibleCols.push_back(col);

        QTableWidgetItem* hdr = tableWidget->horizontalHeaderItem(col);
        if (hdr && hdr->text().contains("Severity", Qt::CaseInsensitive)) {
            severityCol = col;
        }
    }

    QString html;

    html += "<h2>3. Dashboard / Logs</h2>";

    if (visibleCols.isEmpty()) {
        html += "<p>No visible columns to export.</p>";
        return html;
    }

    html += "<table><tr>";

    for (int col : visibleCols) {
        QTableWidgetItem* hdr = tableWidget->horizontalHeaderItem(col);
        QString headerText = hdr ? hdr->text() : QString("Column %1").arg(col);
        html += "<th>" + headerText.toHtmlEscaped() + "</th>";
    }

    html += "</tr>";

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        if (tableWidget->isRowHidden(row))
            continue;

        html += "<tr>";

        for (int col : visibleCols) {
            QString text = getCellText(tableWidget, row, col);

            if (col == severityCol) {
                QString sev = text.toLower();
                QString cssClass = "info";

                if (sev.contains("critical"))
                    cssClass = "critical";
                else if (sev.contains("high"))
                    cssClass = "high";
                else if (sev.contains("medium"))
                    cssClass = "medium";

                html += "<td class='" + cssClass + "'>" + text.toHtmlEscaped() + "</td>";
            }
            else {
                html += "<td>" + text.toHtmlEscaped() + "</td>";
            }
        }

        html += "</tr>";
    }

    html += "</table>";

    return html;
}