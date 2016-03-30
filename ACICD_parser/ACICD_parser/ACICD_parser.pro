TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt

QT       += sql # On rajoute SQL

SOURCES += main.cpp \
    acicd_equipment.cpp \
    acicd.cpp \
    acicd_connector.cpp \
    sql_database_manager.cpp

HEADERS += \
    ../../CSV/csv_common.h \
    ../../CSV/csv_data.h \
    ../../CSV/csv_parser.h \
    ../../CSV/csv_stl_traits.h \
    acicd_header.h \
    acicd_equipment.h \
    acicd.h \
    acicd_connector.h \
    sql_database_manager.h

INCLUDEPATH += ../../CSV/ \
               C:\local\boost_1_60_0
