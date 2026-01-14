#pragma once
#include <QString>
#include<QMap>

class Analyze
{
public:
    Analyze();
    ~Analyze();

    void analyzeLine(const QString& line, QString& eventType, QString& severity);
    void clearLoginCounter(); 

private:
    
    QMap<QString, int> loginfailedCounter;
};

