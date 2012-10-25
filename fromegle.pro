TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += connection.h selector.h text.h poll.h
SOURCES += connection.cpp fromegle.cpp text.cpp poll.cpp

QT += network
CONFIG += debug
