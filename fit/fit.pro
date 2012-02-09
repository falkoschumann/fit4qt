#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T23:18:20
#
#-------------------------------------------------

QT += core
QT -= gui

CONFIG += console warn_on
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    parse.cpp \
    fixture.cpp \
    columnfixture.cpp \
    rowfixture.cpp \
    actionfixture.cpp \
    filerunner.cpp \
    counts.cpp \
    primitivefixture.cpp \
    ../eg/arithmeticfixture.cpp \
    ../eg/arithmeticcolumnfixture.cpp \
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
    ../eg/arithmeticfixture.h \
    ../eg/arithmeticcolumnfixture.h \
    fitexcept.h \
    typeadapter.h

INCLUDEPATH += ..
