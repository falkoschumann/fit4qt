TARGET = tst_frameworktest
TEMPLATE = app
DESTDIR = ../../dist

QT += testlib
QT -= gui
CONFIG += console testcase
CONFIG -= app_bundle

SOURCES += frameworktest.cpp

INCLUDEPATH += ../../libs/
LIBS += -L$${DESTDIR} -lfit
