#include <QCoreApplication>

#include "httpserver.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    HttpServer server(QHostAddress::LocalHost, 1234);
    return a.exec();
}
