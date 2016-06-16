TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT       += sql # On rajoute SQL

TEMPLATE = app

SOURCES += main.cpp \
    micd_parser.cpp

HEADERS += \
    ../../XLS/libxls/include/xls.h \
    micd_parser.h
INCLUDEPATH += ../../XLS/libxls/include/

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../XLS/libxls/lib/ -lxlsreader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../XLS/libxls/lib/ -lxlsreaderd

INCLUDEPATH += $$PWD/../../XLS/libxls/include
DEPENDPATH += $$PWD/../../XLS/libxls/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/C:/MinGW/lib/ -liconv
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/C:/MinGW/lib/ -liconvd

INCLUDEPATH += $$PWD/C:/MinGW/include
DEPENDPATH += $$PWD/C:/MinGW/include
