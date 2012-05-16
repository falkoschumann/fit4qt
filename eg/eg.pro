TEMPLATE = app
DESTDIR = ../dist

QT -= gui
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp \
    arithmeticfixture.cpp \
    arithmeticcolumnfixture.cpp

HEADERS += \
    arithmeticfixture.h \
    arithmeticcolumnfixture.h



INCLUDEPATH += ../
LIBS += -L${DESTDIR} -lfit
