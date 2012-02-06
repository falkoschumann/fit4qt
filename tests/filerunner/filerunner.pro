#-------------------------------------------------
#
# Project created by QtCreator 2012-02-05T23:44:12
#
#-------------------------------------------------

QT += testlib
QT -= gui

TARGET = filerunnertest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    filerunnertest.cpp \
    ../../fit/filerunner.cpp \
    ../../fit/parse.cpp \
    ../../fit/fixture.cpp \
    ../../fit/counts.cpp

HEADERS += \
    ../../fit/filerunner.h \
    ../../fit/parse.h \
    ../../fit/fixture.h \
    ../../fit/counts.h

INCLUDEPATH += ../..

QMAKE_CXXFLAGS += -g -pg -fprofile-arcs -ftest-coverage
LIBS += -L/Developer/usr/lib -lprofile_rt
