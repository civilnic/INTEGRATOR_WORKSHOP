TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT       += sql # On rajoute SQL

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    ../../XLS/libxls/include/libxls/xls.h
INCLUDEPATH += ../../XLS/libxls/include/
