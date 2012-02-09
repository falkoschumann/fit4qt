#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T23:25:27
#
#-------------------------------------------------

TEMPLATE = app
TARGET = testparse
DESTDIR = ../../dist

QT += testlib
QT -= gui

CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    parsetest.cpp \

HEADERS +=

INCLUDEPATH += ../..

LIBS += -L${DESTDIR} -lfit
