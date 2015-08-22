#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->availableRoomsListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onAvailableRoomsListItemClicked(QListWidgetItem*)));
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
