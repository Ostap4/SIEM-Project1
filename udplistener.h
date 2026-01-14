#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>

class UdpListener : public QObject
{
    Q_OBJECT

public:
    explicit UdpListener(QObject* parent = nullptr);
    ~UdpListener(); 

    void startServer(quint16 port);

signals:
   
    void logReceived(const QString& message, const QString& senderIp);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket* socket = nullptr;
    QTimer* poolTimer = nullptr;
};

#endif // UDPLISTENER_H