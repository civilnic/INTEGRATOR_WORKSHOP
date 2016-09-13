#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T22:19:29
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = sql_database_manager
TEMPLATE = lib

DEFINES += SQL_DATABASE_MANAGER_LIBRARY

SOURCES += sql_database_manager.cpp \
    sql_element.cpp

HEADERS += sql_database_manager.h\
        sql_database_manager_global.h \
    sql_element.h

INCLUDEPATH += C:\local\boost_1_60_0

unix {
    target.path = /usr/lib
    INSTALLS += target
}
