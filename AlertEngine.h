#pragma once

#ifndef ALERTENGINE_H
#define ALERTENGINE_H

#include <QString>
#include <QMap>
#include <QList>
#include <QSet>
#include <QDateTime>


class AlertEngine
{
public:
	AlertEngine();
	void trackEvent(const QString& ruleName, const QString& key);
	bool shouldTrigger(const QString ruleName, const QString& key, int threshold, int seconds);
	void clearAll();


private:
	QMap<QString, QMap<QString, QList<qint64>>> events;

	QSet<QString> triggeredAlerts;



};
#endif //ALERTENGINE_H

