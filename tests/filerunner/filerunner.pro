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
    ../../src/fit/filerunner.cpp \
    ../../src/fit/parse.cpp \
    ../../src/fit/fixture.cpp \
    ../../src/fit/counts.cpp

HEADERS += \
    ../../src/fit/filerunner.h \
    ../../src/fit/parse.h \
    ../../src/fit/fixture.h \
    ../../src/fit/counts.h

INCLUDEPATH += ../../src/

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -L/Developer/usr/lib -lprofile_rt
