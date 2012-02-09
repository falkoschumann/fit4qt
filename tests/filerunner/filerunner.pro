#-------------------------------------------------
#
# Project created by QtCreator 2012-02-05T23:44:12
#
#-------------------------------------------------

TEMPLATE = app
TARGET = filerunnertest
DESTDIR = ../../dist

QT += testlib
QT -= gui

CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    filerunnertest.cpp

HEADERS +=

INCLUDEPATH += ../..

QMAKE_CXXFLAGS += -g -pg -fprofile-arcs -ftest-coverage
LIBS += -L/Developer/usr/lib -lprofile_rt

LIBS += -L../../dist -lfit
