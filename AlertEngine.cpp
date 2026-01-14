#include "AlertEngine.h"


AlertEngine::AlertEngine() {}

void AlertEngine::trackEvent(const QString& ruleName, const QString& key)
{
	qint64 now = QDateTime::currentSecsSinceEpoch();

	events[ruleName][key].append(now);

}




bool AlertEngine::shouldTrigger(const QString ruleName, const QString& key, int threshold, int seconds)
{
	if (!events.contains(ruleName) || !events[ruleName].contains(key)) {
		return false;
	}

	qint64 now = QDateTime::currentSecsSinceEpoch();
	QList<qint64>& timestamps = events[ruleName][key];

	while (!timestamps.isEmpty() && (now - timestamps.first() > seconds)) {
		timestamps.removeFirst();
	}

	if (timestamps.size() >= threshold) {
		QString alertKey = ruleName + "_" + key;

		if (!triggeredAlerts.contains(alertKey)) {
			triggeredAlerts.insert(alertKey);
			return true;
		}
		
	}

	return false;
}




void AlertEngine::clearAll()
{
	events.clear();
	triggeredAlerts.clear();

}
