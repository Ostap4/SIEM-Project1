#include "udplistener.h"
#include <QNetworkDatagram>
#include <QDebug>

UdpListener::UdpListener(QObject* parent) : QObject(parent)
{
    
    socket = new QUdpSocket(nullptr);

    
    
    poolTimer = new QTimer(this);

   
    connect(poolTimer, &QTimer::timeout, this, &UdpListener::processPendingDatagrams);

    
    connect(socket, &QUdpSocket::readyRead, this, &UdpListener::processPendingDatagrams);
}

UdpListener::~UdpListener()
{
    if (poolTimer) {
        poolTimer->stop();
        delete poolTimer; 
    }

    if (socket) {
        socket->close();
        socket->deleteLater();
        socket = nullptr;
    }
}

void UdpListener::startServer(quint16 port)
{
    if (!socket) return;

    if (socket->state() != QAbstractSocket::UnconnectedState)
        socket->close();

    //127.0.0.1 (LocalHost)
    
    bool bound = socket->bind(QHostAddress("127.0.0.1"), port, QUdpSocket::ShareAddress);

    if (bound) {
        qDebug() << ">>> SERWER START: 127.0.0.1 Port:" << port;

        
        poolTimer->start(200);
    }
    else {
        qDebug() << ">>> ERROR BIND:" << socket->errorString();
    }
}

void UdpListener::processPendingDatagrams()
{
    if (!socket) return;

    
    while (socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket->receiveDatagram();

        QByteArray data = datagram.data();
        QString message = QString::fromUtf8(data);
        QString senderIp = datagram.senderAddress().toString();

        
        if (senderIp.startsWith("::ffff:")) {
            senderIp = senderIp.mid(7);
        }

        qDebug() << "!!! LOG RECIVED !!! :" << message;

        emit logReceived(message, senderIp);
    }
}