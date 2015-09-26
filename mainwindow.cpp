#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QByteArray>
#include "sample.h"
#include "peer.h"
#include <QNetworkInterface>
#include <QMessageBox>
#include "message.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //To connect signal raised by clicking on room in available room list to slot that contains function to display room details.
    connect(ui->availableRoomsListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onAvailableRoomsListItemClicked(QListWidgetItem*)));

    //Creating new TCP connection to communicate to client
    server = new QTcpServer(this);

    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 15000))
    {   // this message should be added to GUI
         qDebug() << "Server could not start";
    }
    else{

        qDebug() << "Server started!";
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
//Function to create room and to add room to the list of available rooms
int MainWindow::on_createBtn_clicked()
{

    QString roomDesc = ui->roomDesc->text();
    QString roomName = ui->roomName->text();
    if(roomName.isEmpty() == true){
        QMessageBox box;
        box.setText("Oops! Room Name empty.Please enter valid Room Name.");
        box.exec();
        return -1;

    }

    if(rooms.contains(roomName) == true)
    {
        QMessageBox box;
        box.setText("Sorry! Room Name already occupied.");
        box.exec();
        return -1;
    }


    int portNumber = MainWindow::portNum++;
    Room room = Room( roomName, roomDesc, portNumber );

    qDebug() << room.getRoomName();
    qDebug() << room.getRoomDesc();
    qDebug() << room.getPort();

   // room.addNickName("Vivek");
   // room.addNickName("Dipesh");
   // room.addNickName("Haresh");
    ui->availableRoomsListWidget->addItem(room.getRoomName());

    MainWindow::rooms.insert(room.getRoomName(),room);
return 0;

}
//Function to display room description when room is selected from available room list
void MainWindow::onAvailableRoomsListItemClicked(QListWidgetItem *listItem){

   ui->infoPanelTextBox->clear();
    Room room = MainWindow::rooms.value(listItem->text());
    QString roomName = "Room name: "+room.getRoomName()+"\n";
    QString roomPort = "Listening port: "+QString::number(room.getPort())+"\n";
    QString roomDiscussion = "Discussion topic: "+room.getRoomDesc()+"\n";
   // qDebug() << roomName;
    QString roomConnectedNicks = "Connected Nicks: \n";

    for (Peer peer: room.getJoinedNickNames()) {
       roomConnectedNicks.append(peer.getNickName()+"\n");
    }

    ui->infoPanelTextBox->insertPlainText(roomName+"\n");
    ui->infoPanelTextBox->insertPlainText(roomPort+"\n");
    ui->infoPanelTextBox->insertPlainText(roomDiscussion+"\n");
    ui->infoPanelTextBox->insertPlainText(roomConnectedNicks+"\n");


}

//Function to handle clients connecting to sockets and to send them list of available rooms
void MainWindow::newConnection()
{
    // Get socket for pending connection

  /*  Sample s;
    s.message = "Hello classes!";
    s.sender = "Vivek Pandya";
*/
  /* QHostAddress ownIPaddress;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            ownIPaddress = address;
    }

    Peer peer = Peer("Dipu Bhai",ownIPaddress);
    Peer peer1 = Peer("LLVM_Ninja", ownIPaddress);


Message message = Message(MessageType::RoomDetails);
message.insertDataString("Hello World");
message.insertDataString("C++ is difficult , but when you are used to it every thing becomes easy.");
message.insertPeerObj(peer);
message.insertPeerObj(peer1);
*/
    while(server->hasPendingConnections()){

        QTcpSocket *socket = server->nextPendingConnection();
        connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
       /* QByteArray block;
        QDataStream out(&block, QIODevice::ReadWrite);
        out.setVersion(QDataStream::Qt_5_5);
    //! [4] //! [6]
        out << (quint16)0;
        //out << s;
        //out << peer;
        out << message;
        out.device()->seek(0);

        out << (quint16)(block.size() - sizeof(quint16));
    //! [6] //! [7]
       qDebug()<<QString(block);
       socket->write(block);
       socket->flush();

       socket->waitForBytesWritten(3000);
       qDebug()<<"Here!";
*/
    }


/*
    QTcpSocket *socket = server->nextPendingConnection();
    QString responseString;
    QHash<QString, Room>::iterator i;
    for (i = MainWindow::rooms.begin(); i != MainWindow::rooms.end(); ++i){
       Room room = i.value();
    responseString.append(room.getRoomName()+":"+QString::number(room.getPort())+":");
    }
    //To convert QString object to Character Pointer for Write Function of Socket.
    QByteArray tempByteArray = responseString.toUtf8();
    const char *tempChar = tempByteArray.data();
    socket->write(tempChar);

    socket->flush();

    socket->waitForBytesWritten(3000);
    */
    //socket->close();

    //Note: The returned QTcpSocket object cannot be used from another thread.
    //If you want to use an incoming connection from another thread,
    //you need to override incomingConnection().
}

void MainWindow::readyRead(){
    qDebug()<<"Ok";
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());

    quint16 blockSize=0;
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_5);

    if (blockSize == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
            return;
//! [8]

//! [10]
        in >> blockSize;
    }

    if (socket->bytesAvailable() < blockSize)
        return;
//! [10] //! [11]

   // Sample sample;
   // in >> sample;
   // qDebug() << sample.message+"Message Recieved";
   // qDebug()<<sample.sender+"From Sender ";
   // Peer peer;
    //in >> peer;

    //qDebug() << peer.getNickName();
    //qDebug() << peer.getpeerAddress();
    Message message ;
    in >> message;
    MessageType mtype = message.getMessageType();
    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_5_5);
           out << (quint16)0;
           //out << s;
           //out << peer;



    if (mtype == MessageType::GetRoomDetails){
        Message response = Message(MessageType::RoomDetails);
        qDebug() <<"GetRoomDetails";
        // Give all available rooms in reply
        QHash<QString, Room>::iterator i;
        for (i = MainWindow::rooms.begin(); i != MainWindow::rooms.end(); ++i){
           Room room = i.value();
           response.insertRoomObj(room);

        }
        out << response;
        out.device()->seek(0);

        out << (quint16)(block.size() - sizeof(quint16));
    //! [6] //! [7]
       qDebug()<<QString(block);
       socket->write(block);
       socket->flush();

       socket->waitForBytesWritten(3000);

    }
    else if(mtype == MessageType::JoinRoom){
         qDebug() <<"JoinRoom";
         for(QString roomName: message.getDataStrings()){
             qDebug() << roomName +"Room name received";
             Room room = MainWindow::rooms[roomName];
            for(Peer peer: message.getPeerVector()){
             room.addNickName(peer);
            }

             rooms[roomName] = room;
         }

    }
    else if(mtype == MessageType::LeaveRoom){
         qDebug() <<"LeaveRoom";
         for(QString roomName: message.getDataStrings()){
             Room room = MainWindow::rooms[roomName];
            for(Peer peer: message.getPeerVector()){
             room.removeNickName(peer);
            }

             rooms[roomName] = room;
         }

    }




   /* while(socket->bytesAvailable()){

        QString command = QString::fromLatin1(socket->readAll());
        qDebug() << command << "Command ";

        QStringList stringList = command.split(":",QString::SkipEmptyParts);

        for (QStringList::iterator it = stringList.begin();
                 it != stringList.end(); ++it) {
            qDebug() << *it;
        }

        if(stringList.begin()->compare("getRoomDetails") == 0){

            // need to send room details
            QString responseString;
            QHash<QString, Room>::iterator i;
            for (i = MainWindow::rooms.begin(); i != MainWindow::rooms.end(); ++i){
               Room room = i.value();
            responseString.append(room.getRoomName()+":"+QString::number(room.getPort())+":");
            }
            //To convert QString object to Character Pointer for Write Function of Socket.
            QByteArray tempByteArray = responseString.toUtf8();
            const char *tempChar = tempByteArray.data();
            socket->write(tempChar);

            socket->flush();

            socket->waitForBytesWritten(3000);
        }
        else if(stringList.begin()->compare("joinRoom") ==0) {
            qDebug() <<"Logic works";
            QString nickName = stringList.at(1);
            QString roomName = stringList.at(2);
           Room room = MainWindow::rooms[roomName];
           room.addNickName(nickName);
           rooms[roomName] = room;
            qDebug() << nickName << " : " << roomName <<'\n';

        }
        else if(stringList.begin()->compare("leaveRoom") == 0){
            QString nickName = stringList.at(1);
            QString roomName = stringList.at(2);
            Room room = MainWindow::rooms[roomName];
            room.removeNickName(nickName);
            rooms[roomName] = room;

            qDebug() << nickName << " : " << roomName << "Leave room"<<'\n';


        }
    } */
}

void MainWindow::disconnected(){

    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

        socket->deleteLater();

}
