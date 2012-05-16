TARGET = tst_parsetest
TEMPLATE = app
DESTDIR = ../../dist

QT += testlib
QT -= gui
CONFIG += console testcase
CONFIG -= app_bundle

SOURCES += parsetest.cpp

INCLUDEPATH += ../../
LIBS += -L${DESTDIR} -lfit
