TARGET = tst_frameworktest
TEMPLATE = app

QT += testlib
QT -= gui
CONFIG += console testcase
CONFIG -= app_bundle

SOURCES += frameworktest.cpp

INCLUDEPATH += ../../libs/
LIBS += -L../../libs/fit -lfit
