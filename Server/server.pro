#-------------------------------------------------
#
# Project created by QtCreator 2013-11-12T11:53:37
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    clienthandler.cpp \
    databasehelper.cpp \
    mailmessage.cpp

HEADERS  += \
    server.h \
    clienthandler.h \
    databasehelper.h \
    mailmessage.h
