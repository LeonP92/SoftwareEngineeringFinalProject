#-------------------------------------------------
#
# Project created by QtCreator 2013-11-12T11:53:37
#
#-------------------------------------------------

QT       += sql network testlib
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestServer
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app


SOURCES += \
    server.cpp \
    clienthandler.cpp \
    databasehelper.cpp \
    mailmessage.cpp \
    testserver.cpp

HEADERS  += \
    server.h \
    clienthandler.h \
    databasehelper.h \
    mailmessage.h
