#-------------------------------------------------
#
# Project created by QtCreator 2016-04-03T23:52:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = logo_recognition
TEMPLATE = app


SOURCES += main.cpp\
        logo_detect.cpp

HEADERS  += logo_detect.h

FORMS    += logo_detect.ui
INCLUDEPATH += C:/opencv/build/install/include
LIBS += "C:/opencv/build/bin/*.dll"
