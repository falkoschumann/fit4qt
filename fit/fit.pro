#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T23:18:20
#
#-------------------------------------------------

TEMPLATE = lib
VERSION = 0.3.0
DESTDIR = ../dist

QT += core
QT -= gui

CONFIG += dll warn_on
CONFIG -= lib_bundle


SOURCES += \
    parse.cpp \
    fixture.cpp \
    columnfixture.cpp \
    rowfixture.cpp \
    actionfixture.cpp \
    filerunner.cpp \
    counts.cpp \
    primitivefixture.cpp \
    typeadapter.cpp

HEADERS += \
    parse.h \
    fixture.h \
    columnfixture.h \
    rowfixture.h \
    actionfixture.h \
    filerunner.h \
    counts.h \
    primitivefixture.h \
    fitexcept.h \
    typeadapter.h

INCLUDEPATH += ..
