#-------------------------------------------------
#
# Project created by QtCreator 2012-02-05T23:44:12
#
#-------------------------------------------------

TEMPLATE = app
TARGET = testfilerunner
DESTDIR = ../../dist

QT += testlib
QT -= gui

CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    filerunnertest.cpp

HEADERS +=

INCLUDEPATH += ../..

LIBS += -L${DESTDIR} -lfit
