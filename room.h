#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QString>
#include <QHostAddress>
#include <QSet>

class Room
{



public:
    Room();

    Room( QString roomName1, QString roomDesc1, int  portNum);

    QString getRoomName() const;
    void setRoomName(const QString &roomName1);

    QString getRoomDesc() const;
    void setRoomDesc(const QString &roomDesc1);

    int getPort() const;
    void setPort(int portNum);

    QSet<QString> getJoinedNickNames() const;
    void setJoinedNickNames(const QSet<QString> &joinedNickNames1);

    void addNickName(const QString &nickName);


private:
    // To hold room name
    QString roomName;
    // To hold room description
    QString roomDesc;
    // This variable holds multicast group port
    int port;

    // To hold list of nick names connected to this room
    // Need to change this to QSet
    QSet<QString> joinedNickNames;

};

#endif // ROOM_H
