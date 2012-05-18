TARGET = tst_parsetest
TEMPLATE = app

QT += testlib
QT -= gui
CONFIG += console testcase
CONFIG -= app_bundle

SOURCES += parsetest.cpp

INCLUDEPATH += ../../libs/
LIBS += -L../../libs/fit -lfit
