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
    ../../fit/fixture.cpp \
    frameworktest.cpp \
    ../../fit/parse.cpp \
    ../../fit/counts.cpp

HEADERS += \
    ../../fit/fixture.h \
    ../../fit/parse.h \
    ../../fit/counts.h

INCLUDEPATH += ../../

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -L/Developer/usr/lib -lprofile_rt
