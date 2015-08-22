#include "mainwindow.h"
#include <QApplication>
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    TCPServer server;


    return a.exec();
}
