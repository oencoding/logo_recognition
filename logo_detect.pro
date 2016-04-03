#-------------------------------------------------
#
# Project created by QtCreator 2016-04-03T22:19:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = logo_recognition
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
INCLUDEPATH += C:/opencv/build/install/include
LIBS += "C:/opencv/build/bin/*.dll"
