#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T23:25:27
#
#-------------------------------------------------

QT += testlib
QT -= gui

TARGET = parsetest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    parsetest.cpp \
    ../../src/fit/parse.cpp

HEADERS += \
    ../../src/fit/parse.h

INCLUDEPATH += ../../src/

QMAKE_CXXFLAGS += -g -pg -fprofile-arcs -ftest-coverage
LIBS += -L/Developer/usr/lib -lprofile_rt
