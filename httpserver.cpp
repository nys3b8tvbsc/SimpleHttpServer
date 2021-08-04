#include "httpserver.h"
#include "socketthread.h"

#include <QTcpSocket>
#include <QThread>

HttpServer::HttpServer(const QHostAddress& host, quint16 port, QObject* parent)
    : QTcpServer(parent)
{
    if (listen(host, port)) {
        qDebug() << "Listening to port " << port;
    } else {
        qDebug() << "Start failure";
    }
}

void HttpServer::incomingConnection(qintptr handle)
{
    qDebug() << "New connection";
    SocketThread* thread = new SocketThread(handle, this);
    connect(thread, &SocketThread::finished, thread, &SocketThread::deleteLater);

    thread->start();
}
