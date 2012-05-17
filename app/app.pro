TEMPLATE = app
TARGET = fit
DESTDIR = ../dist

QT -= gui
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp

INCLUDEPATH += ../libs/
LIBS += -L${DESTDIR} -lfit
