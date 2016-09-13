TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT       += sql # On rajoute SQL

QMAKE_CXXFLAGS += -D__NO_INLINE__

TEMPLATE = app

SOURCES += main.cpp \
    ../../SQL_manager/sql_database_manager.cpp \
    micd_document.cpp \
    micd_element.cpp

HEADERS += \
    ../../XLS/libxls/include/xls.h \
    micd_header.h \
    ../../SQL_manager/sql_database_manager.h \
    micd_document.h \
    micd_element.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../SQL_manager/sql_database_manager/release/ -lsql_database_manager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../SQL_manager/sql_database_manager/debug/ -lsql_database_manager

INCLUDEPATH += $$PWD/../../SQL_manager/sql_database_manager/release
DEPENDPATH += $$PWD/../../SQL_manager/sql_database_manager/release

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../SQL_manager/sql_database_manager/release/libsql_database_manager.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../SQL_manager/sql_database_manager/debug/libsql_database_manager.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../SQL_manager/sql_database_manager/release/sql_database_manager.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../SQL_manager/sql_database_manager/debug/sql_database_manager.lib
