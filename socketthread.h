#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QTcpSocket>
#include <QThread>

class SocketThread : public QThread {
public:
    explicit SocketThread(qintptr socket_descriptor, QObject* parent = nullptr);

private:
    QTcpSocket* _socket;
    qintptr _socketDescriptor;

    // QThread interface
protected:
    void run() override;

public slots:
    void read();
    void disconnect();
};

QByteArray createResponse(const QByteArray& request);

#endif // SOCKETTHREAD_H
