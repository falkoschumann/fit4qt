TEMPLATE = app
TARGET = fit

QT -= gui
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp

INCLUDEPATH += ../libs/
LIBS += -L../libs/fit -lfit
