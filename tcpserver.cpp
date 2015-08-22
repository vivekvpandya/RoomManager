#include "tcpserver.h"

TCPServer::TCPServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);

    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 15000))
    {   // this message should be added tp GUI
         qDebug() << "Server could not start";
    }
    else{

        qDebug() << "Server started!";
    }



}

void TCPServer::newConnection()
{
    // Get socket for pending connection
    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("Connected to the server!");
    socket->flush();

    socket->waitForBytesWritten(3000);
    socket->close();

    //Note: The returned QTcpSocket object cannot be used from another thread.
    //If you want to use an incoming connection from another thread,
    //you need to override incomingConnection().
}
