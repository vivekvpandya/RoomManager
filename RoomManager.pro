#-------------------------------------------------
#
# Project created by QtCreator 2015-08-19T00:47:03
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoomManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    room.cpp \
    sample.cpp \
    peer.cpp \
    message.cpp

HEADERS  += mainwindow.h \
    room.h \
    sample.h \
    peer.h \
    message.h

FORMS    += mainwindow.ui
