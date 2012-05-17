TEMPLATE = lib
VERSION = 0.3.0
DESTDIR = ../../dist

QT -= gui

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
    summary.cpp \
    fixtureregistry.cpp \
    utilities.cpp

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
    summary.h \
    fixtureregistry.h \
    fitplugin.h \
    utilities.h
