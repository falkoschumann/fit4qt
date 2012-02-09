#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T23:25:27
#
#-------------------------------------------------

TEMPLATE = app
TARGET = frameworktest

QT += testlib
QT -= gui

CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    frameworktest.cpp

HEADERS +=

INCLUDEPATH += ../..

QMAKE_CXXFLAGS += -g -pg -fprofile-arcs -ftest-coverage
LIBS += -L/Developer/usr/lib -lprofile_rt

LIBS += -L../../fit -lfit
