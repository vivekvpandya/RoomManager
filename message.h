#ifndef MESSAGE_H
#define MESSAGE_H


class Message
{
public:
    Message();

    enum MessageType{
        RoomListReq, RoomListRes, JoinRoom, LeaveRoom, ChatMessage
    };

    MessageType messageType() const;
    void setMessageType(MessageType messageType);

    const QList<QObject> &parameterList() const;
    void setParameterList(const QList<QObject> &parameterList);

    const QList<QObject> &data() const;
    void setData(const QList<QObject> &data);

    void read(const QJsonObject &josn);
    void write(QJsonObject &json) const;

private:
    MessageType mMessageType;
    QList<QObject> mparameterList;
    QList<QObject> mdata;



};

#endif // MESSAGE_H
