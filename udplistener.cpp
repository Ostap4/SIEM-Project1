#include "udplistener.h"
#include <QNetworkDatagram>
#include <QDebug>

UdpListener::UdpListener(QObject* parent) : QObject(parent)
{
    // 1. Socket bez rodzica 
    socket = new QUdpSocket(nullptr);

    // 2. TWORZYMY RADAR (TIMER)
    
    poolTimer = new QTimer(this);

    // Timer będzie wywoływał funkcję odczytu co chwilę
    connect(poolTimer, &QTimer::timeout, this, &UdpListener::processPendingDatagrams);

    // Dla pewności zostawiamy też oryginalny sygnał
    connect(socket, &QUdpSocket::readyRead, this, &UdpListener::processPendingDatagrams);
}

UdpListener::~UdpListener()
{
    if (poolTimer) {
        poolTimer->stop();
        delete poolTimer; // Timer ma rodzica (this), ale dla czystości
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

    // ZMIANA: Bindujemy konkretnie do 127.0.0.1 (LocalHost)
    
    bool bound = socket->bind(QHostAddress("127.0.0.1"), port, QUdpSocket::ShareAddress);

    if (bound) {
        qDebug() << ">>> SERWER START: 127.0.0.1 Port:" << port;

        // URUCHAMIAMY RADAR
        // Co 200ms sprawdzamy "ręcznie", czy są dane.
        poolTimer->start(200);
    }
    else {
        qDebug() << ">>> BŁĄD BIND:" << socket->errorString();
    }
}

void UdpListener::processPendingDatagrams()
{
    if (!socket) return;

    // Pętla pobierająca WSZYSTKIE oczekujące pakiety
    while (socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket->receiveDatagram();

        QByteArray data = datagram.data();
        QString message = QString::fromUtf8(data);
        QString senderIp = datagram.senderAddress().toString();

        // Usuwamy prefiksy IPv6 jeśli się pojawią
        if (senderIp.startsWith("::ffff:")) {
            senderIp = senderIp.mid(7);
        }

        qDebug() << "!!! LOG ODEBRANY !!! :" << message;

        emit logReceived(message, senderIp);
    }
}