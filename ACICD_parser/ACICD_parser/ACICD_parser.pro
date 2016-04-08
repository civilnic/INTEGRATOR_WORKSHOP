TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt

QT       += sql # On rajoute SQL

SOURCES += main.cpp \
    acicd_equipment.cpp \
    acicd_connector.cpp \
    sql_database_manager.cpp \
    acicd_document.cpp \
    acicd_element.cpp \
    acicd_connector_line_type.cpp \
    acicd_connector_pin_role.cpp \
    acicd_connection_name.cpp \
    acicd_connector_pin.cpp

HEADERS += \
    ../../CSV/csv_common.h \
    ../../CSV/csv_data.h \
    ../../CSV/csv_parser.h \
    ../../CSV/csv_stl_traits.h \
    acicd_header.h \
    acicd_equipment.h \
    acicd_connector.h \
    sql_database_manager.h \
    acicd_document.h \
    acicd_element.h \
    acicd_connector_line_type.h \
    acicd_connector_pin_role.h \
    acicd_connection_name.h \
    acicd_connector_pin.h

INCLUDEPATH += ../../CSV/ \
               C:\local\boost_1_60_0
