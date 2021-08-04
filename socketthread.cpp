#include "socketthread.h"

SocketThread::SocketThread(qintptr socketDescriptor, QObject* parent)
    : QThread(parent)
    , _socketDescriptor(socketDescriptor)
{
}

void SocketThread::run()
{
    _socket = new QTcpSocket();
    _socket->setSocketDescriptor(_socketDescriptor);

    connect(_socket, &QTcpSocket::readyRead, this, &SocketThread::read, Qt::DirectConnection);
    connect(_socket, &QTcpSocket::disconnected, this, &SocketThread::disconnect, Qt::DirectConnection);

    qDebug() << "Connected desc №" << _socketDescriptor;

    exec();
}

void SocketThread::read()
{
    QByteArray request = _socket->readAll();

    qDebug() << request;

    _socket->write(createResponse(request));
}

void SocketThread::disconnect()
{
    qDebug() << "Disconnected desc №" << _socketDescriptor;
    _socket->close();

    quit();
}

QByteArray createResponse(const QByteArray& request)
{
    QList<QByteArray> tokens = request.split(' ');
    QByteArray response("HTTP/1.1 ");
    if ("/test" == tokens[1]) {
        QByteArray html = "<!DOCTYPE html>\n<html>\n<title>localhost/test</title>\n<body>\n<p>Welcome to /test.</p>\n</body>\n</html>";

        response += "200 OK\r\nContent-Type: text/html\r\nContent-Length: ";
        response += QByteArray::number(html.size());
        response += "\r\n\r\n";
        response += html;
    } else {
        QByteArray html = "<!DOCTYPE html>\n<html>\n<title>localhost/nothing</title>\n<body>\n<p>Error. Please try /test.</p>\n</body>\n</html>";

        response += "404 Not Found\r\nContent-Type: text/html\r\nContent-Length: ";
        response += QByteArray::number(html.size());
        response += "\r\n\r\n";
        response += html;
    }
    return response;
}
