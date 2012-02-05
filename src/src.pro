#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T23:18:20
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = fit
CONFIG   += console warn_on
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += fit/main.cpp \
    fit/parse.cpp \
    fit/fixture.cpp \
    fit/columnfixture.cpp \
    fit/rowfixture.cpp \
    fit/actionfixture.cpp \
    fit/filerunner.cpp \
    fit/counts.cpp \
    fit/primitivefixture.cpp \
    eg/arithmeticfixture.cpp

HEADERS += \
    fit/parse.h \
    fit/fixture.h \
    fit/columnfixture.h \
    fit/rowfixture.h \
    fit/actionfixture.h \
    fit/filerunner.h \
    fit/counts.h \
    fit/primitivefixture.h \
    eg/arithmeticfixture.h \
    muspellheim/muspellheimexcept.h
