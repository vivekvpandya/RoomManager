#-------------------------------------------------
#
# Project created by QtCreator 2015-08-19T00:47:03
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoomManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    room.cpp

HEADERS  += mainwindow.h \
    room.h

FORMS    += mainwindow.ui
