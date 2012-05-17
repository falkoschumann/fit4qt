TARGET = tst_filerunnertest
TEMPLATE = app
DESTDIR = ../../dist

QT += testlib
QT -= gui
CONFIG += console testcase
CONFIG -= app_bundle

SOURCES += filerunnertest.cpp

INCLUDEPATH += ../../libs/
LIBS += -L$${DESTDIR} -lfit
