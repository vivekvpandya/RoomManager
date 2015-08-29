#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "room.h"
#include <QListWidgetItem>
#include <QTcpSocket>
#include <QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_createBtn_clicked();
    void onAvailableRoomsListItemClicked(QListWidgetItem *listItem);
    void newConnection();
    void disconnected();
    void readyRead();



private:
    Ui::MainWindow *ui;
    int portNum = 10000;
    QHash<QString, Room> rooms;
    QTcpServer *server;

};

#endif // MAINWINDOW_H
