#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "room.h"
#include <QListWidgetItem>

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

private:
    Ui::MainWindow *ui;
    int portNum = 10000;
    QHash<QString, Room> rooms;

};

#endif // MAINWINDOW_H
