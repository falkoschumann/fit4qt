TARGET = tst_filerunnertest
TEMPLATE = app

QT += testlib
QT -= gui
CONFIG += console testcase
CONFIG -= app_bundle

SOURCES += filerunnertest.cpp

INCLUDEPATH += ../../libs/
LIBS += -L../../libs/fit -lfit
