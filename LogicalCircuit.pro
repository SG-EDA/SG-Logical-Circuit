TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    node.cpp \
    script.cpp

HEADERS += \
    gate.h \
    node.h \
    help.h \
    script.h
