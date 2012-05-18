TEMPLATE = lib

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
LIBS += -L../../libs/fit -lfit
