#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T23:25:27
#
#-------------------------------------------------

QT       += testlib
QT       -= gui

TARGET = parsetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    ../../fit/parse.cpp \
    parsetest.cpp

#DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../fit/parse.h

INCLUDEPATH += ../../

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -L/Developer/usr/lib -lprofile_rt
