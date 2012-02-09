#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T23:25:27
#
#-------------------------------------------------

QT += testlib
QT -= gui

TARGET = frameworktest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    frameworktest.cpp \
    ../../fit/fixture.cpp \
    ../../fit/parse.cpp \
    ../../fit/counts.cpp \
    ../../fit/typeadapter.cpp

HEADERS += \
    ../../fit/fixture.h \
    ../../fit/parse.h \
    ../../fit/counts.h \
    ../../fit/typeadapter.h

INCLUDEPATH += ../..

QMAKE_CXXFLAGS += -g -pg -fprofile-arcs -ftest-coverage
LIBS += -L/Developer/usr/lib -lprofile_rt
