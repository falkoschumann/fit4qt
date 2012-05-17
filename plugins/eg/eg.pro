TEMPLATE = lib
DESTDIR = ../../dist/plugins

QT -= gui
CONFIG += plugin

SOURCES += \
    arithmeticfixture.cpp \
    arithmeticcolumnfixture.cpp \
    egplugin.cpp

HEADERS += \
    arithmeticfixture.h \
    arithmeticcolumnfixture.h \
    egplugin.h

INCLUDEPATH += ../../libs/
LIBS += -L../../dist/ -lfit
