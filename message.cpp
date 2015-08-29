#include "message.h"

Message::Message()
{

}

void Message::messageType() const{

    return mMessageType;
}

void Message::setMessageType(MessageType messageType){

    mMessageType = messageType;
}

  const QList<QObject> &Message::parameterList() const{
      return mparameterList;
  }

  void Message::setParameterList(const QList<QObject> &parameterList){

      mparameterList = parameterList;
  }

  const QList<QObject> &Message::data() const{

      return mdata;
  }


  void Message::setData(const QList<QObject> &data){

      mdata = data;
  }


  void Message::read(const QJsonObject &josn){

      mMessageType = MessageType(qRound(json["messageType"].toDouble()));
      mdata.clear();
      QJsonArray mdataArray = json["data"].toArray();
      for (int dataIndex = 0; dataIndex < mdataArray.size(); ++dataIndex){


      }
  }


  void Message::write(QJsonObject &json) const{

      json["messageType"] = mMessageType;

  }
