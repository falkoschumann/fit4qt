#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T23:25:27
#
#-------------------------------------------------

QT       += testlib
QT       -= gui

TARGET = frameworktest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    ../../src/fit/fixture.cpp \
    frameworktest.cpp \
    ../../src/fit/parse.cpp \
    ../../src/fit/counts.cpp

HEADERS += \
    ../../src/fit/fixture.h \
    ../../src/fit/parse.h \
    ../../src/fit/counts.h

INCLUDEPATH += ../../src/

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -L/Developer/usr/lib -lprofile_rt
