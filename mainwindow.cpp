#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QByteArray>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->availableRoomsListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onAvailableRoomsListItemClicked(QListWidgetItem*)));

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_createBtn_clicked()
{

    QString roomDesc = ui->roomDesc->text();
    QString roomName = ui->roomName->text();

    int portNumber = MainWindow::portNum++;
    Room room = Room( roomName, roomDesc, portNumber );

    qDebug() << room.getRoomName();
    qDebug() << room.getRoomDesc();
    qDebug() << room.getPort();

    room.addNickName("Vivek");
    room.addNickName("Dipesh");
    room.addNickName("Haresh");
    ui->availableRoomsListWidget->addItem(room.getRoomName());

    MainWindow::rooms.insert(room.getRoomName(),room);

}

void MainWindow::onAvailableRoomsListItemClicked(QListWidgetItem *listItem){

   ui->infoPanelTextBox->clear();
    Room room = MainWindow::rooms.value(listItem->text());
    QString roomName = "Room name: "+room.getRoomName()+"\n";
    QString roomPort = "Listining port: "+QString::number(room.getPort())+"\n";
    QString roomDiscussion = "Discussion topic: "+room.getRoomDesc()+"\n";
   // qDebug() << roomName;
    QString roomConnectedNicks = "Connected nicks: \n";
    foreach (QString nick, room.getJoinedNickNames()) {
       roomConnectedNicks.append(nick+"\n");
    }

    ui->infoPanelTextBox->insertPlainText(roomName+"\n");
    ui->infoPanelTextBox->insertPlainText(roomPort+"\n");
    ui->infoPanelTextBox->insertPlainText(roomDiscussion+"\n");
    ui->infoPanelTextBox->insertPlainText(roomConnectedNicks+"\n");


}


void MainWindow::newConnection()
{
    // Get socket for pending connection
    QTcpSocket *socket = server->nextPendingConnection();
    QString responseString;
    QHash<QString, Room>::iterator i;
    for (i = MainWindow::rooms.begin(); i != MainWindow::rooms.end(); ++i){
       Room room = i.value();
    responseString.append(room.getRoomName()+":"+QString::number(room.getPort())+"\n");
    }
    QByteArray ba = responseString.toLatin1();
    const char *c_str2 = ba.data();
    socket->write(c_str2);
    socket->flush();

    socket->waitForBytesWritten(3000);
    socket->close();

    //Note: The returned QTcpSocket object cannot be used from another thread.
    //If you want to use an incoming connection from another thread,
    //you need to override incomingConnection().
}
