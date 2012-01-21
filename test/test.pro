#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T23:25:27
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = runtests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    ../fit/fixture.cpp \
    ../fit/parse.cpp \
    parsetest.cpp \
    frameworktest.cpp

#DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../fit/fixture.h \
    ../fit/parse.h \
    parsetest.h \
    frameworktest.h

INCLUDEPATH += ../

#QMAKE_CXXFLAGS_DEBUG += -g -pg -fprofile-arcs -ftest-coverage
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -L/Developer/usr/lib -lprofile_rt
