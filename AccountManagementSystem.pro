TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    account.cpp \
    screenprinter.cpp \
    optionadapter.cpp \
    accountfactory.cpp

HEADERS += \
    account.h \
    utils/List.h \
    screenprinter.h \
    optionadapter.h \
    accountfactory.h

INCLUDEPATH += ./utils
