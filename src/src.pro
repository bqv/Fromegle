TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += . ../include

# Input
HEADERS += connection.h selector.h text.h poll.h json.h mode.h
SOURCES += connection.cpp fromegle.cpp text.cpp poll.cpp json.cpp

LIBS += ../qjson/libqjson.a
TARGET = ../fromegle

QT += network
CONFIG += debug
