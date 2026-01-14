#include "Analyze.h"
#include <QTextStream>
#include <QRegularExpression>


Analyze::Analyze() {}
Analyze::~Analyze() {}

void Analyze::analyzeLine(const QString& line, QString& eventType, QString& severity){
    
    eventType = "Unknown";
    severity = "Info";

    QRegularExpression ipRegex("\\b(?:\\d{1,3}\\.){3}\\d{1,3}\\b");
    QRegularExpressionMatch match = ipRegex.match(line);

    if (match.hasMatch()) {
        QString ip = match.captured(0);

        if (line.contains("Failed password", Qt::CaseInsensitive))
        {
            eventType = "Login Failure";
            severity = "High"; 

            loginfailedCounter[ip]++;
           
            if (loginfailedCounter[ip] >= 3) {
                severity = "Critical";
            }
        }
        else if (line.contains("Accepted password", Qt::CaseInsensitive))
        {
            eventType = "Login Success";
            severity = "Info";
            
        }
        else if (line.contains("500 Internal Server Error", Qt::CaseInsensitive))
        {
            eventType = "Server Error";
            severity = "Medium";
        }
        else if (line.contains("unauthorized", Qt::CaseInsensitive))
        {
            eventType = "Access Denied";
            severity = "High";
        } 
    }
}


void Analyze::clearLoginCounter() {
    loginfailedCounter.clear();
}


