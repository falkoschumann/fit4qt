#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T23:18:20
#
#-------------------------------------------------

TEMPLATE = app
DESTDIR = ../dist

QT += core
QT -= gui

CONFIG += console warn_on
CONFIG -= app_bundle

SOURCES += main.cpp \
    arithmeticfixture.cpp \
    arithmeticcolumnfixture.cpp

HEADERS += \
    arithmeticfixture.h \
    arithmeticcolumnfixture.h

INCLUDEPATH += ..

LIBS += -L../dist -lfit
