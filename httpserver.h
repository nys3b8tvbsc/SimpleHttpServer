#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QTcpServer>

class HttpServer : public QTcpServer {
public:
    HttpServer(const QHostAddress& host, quint16 port = 0, QObject* parent = nullptr);

    // QTcpServer interface
protected:
    void incomingConnection(qintptr handle) override;
};

#endif // HTTPSERVER_H
