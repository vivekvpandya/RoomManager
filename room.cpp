#include "room.h"

Room::Room()
{

}

Room::Room( QString roomName1,  QString roomDesc1, int portNum){

    roomName = roomName1;
    port = portNum;
    roomDesc = roomDesc1;

}


QString Room::getRoomName() const
{
    return roomName;
}

void Room::setRoomName(const QString &roomName1 ){

    roomName = roomName1;
}

int Room::getPort() const
{
    return port;
}

void Room::setPort(int portNum)
{
    port = portNum;
}

QString Room::getRoomDesc() const
{
    return roomDesc;
}

void Room::setRoomDesc(const QString &roomDesc1)
{
    roomDesc = roomDesc1;
}

QSet<QString> Room::getJoinedNickNames() const
{
    return joinedNickNames;
}

void Room::setJoinedNickNames(const QSet<QString> &joinedNickNames1)
{
    joinedNickNames = joinedNickNames1;
}

void Room::addNickName(const QString &nickName){

    joinedNickNames.insert(nickName);

}
