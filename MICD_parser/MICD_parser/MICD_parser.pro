TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT       += sql # On rajoute SQL

TEMPLATE = app

SOURCES += main.cpp \
    ExcelFormat_src/BasicExcel.cpp \
    ExcelFormat_src/ExcelFormat.cpp

HEADERS += \
    ExcelFormat_src/ExcelFormat.h \
    ExcelFormat_src/BasicExcel.h

INCLUDEPATH += ExcelFormat_src
