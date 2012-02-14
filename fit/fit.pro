#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T23:18:20
#
#-------------------------------------------------

include(../fit4qt.pri)
include(../fit4qt-lib.pri)

TEMPLATE = lib
VERSION = 0.3.0

CONFIG += dll

SOURCES += \
    parse.cpp \
    fixture.cpp \
    columnfixture.cpp \
    rowfixture.cpp \
    actionfixture.cpp \
    filerunner.cpp \
    counts.cpp \
    primitivefixture.cpp \
    typeadapter.cpp \
    summary.cpp

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
    typeadapter.h \
    summary.h
