TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT       += sql # On rajoute SQL

QMAKE_CXXFLAGS += -D__NO_INLINE__

TEMPLATE = app

SOURCES += main.cpp \
    ../../SQL_manager/sql_database_manager.cpp \
    micd_document.cpp

HEADERS += \
    ../../XLS/libxls/include/xls.h \
    micd_header.h \
    ../../SQL_manager/sql_database_manager.h \
    micd_document.h

INCLUDEPATH += ../../XLS/libxls/include/
INCLUDEPATH += ../../SQL_manager/

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../XLS/libxls/lib/ -lxlsreader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../XLS/libxls/lib/ -lxlsreaderd

INCLUDEPATH += $$PWD/../../XLS/libxls/include
DEPENDPATH += $$PWD/../../XLS/libxls/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/C:/MinGW/lib/ -liconv
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/C:/MinGW/lib/ -liconvd

INCLUDEPATH += $$PWD/C:/MinGW/include
DEPENDPATH += $$PWD/C:/MinGW/include


INCLUDEPATH += C:\local\boost_1_60_0
