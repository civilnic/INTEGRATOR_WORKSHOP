TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT       += sql # On rajoute SQL

QMAKE_CXXFLAGS += -D__NO_INLINE__

TEMPLATE = app

SOURCES += main.cpp \
    micd_document.cpp \
    micd_element.cpp \
    micd_port_in.cpp \
    micd_port_out.cpp \
    micd_unit.cpp \
    micd_data_type.cpp \
    micd_com_format.cpp \
    micd_com_mode.cpp \
    micd_interface_level.cpp \
    micd_port_name.cpp \
    micd_simple_tab.cpp \
    micd_description.cpp \
    micd_convention.cpp \
    micd_from_to.cpp \
    micd_enum.cpp \
    micd_cons_prod_if.cpp \
    micd_aircraft_signal_name.cpp

HEADERS += \
    ../../XLS/libxls/include/xls.h \
    micd_header.h \
    micd_document.h \
    micd_element.h \
    micd_port_in.h \
    micd_port_out.h \
    micd_unit.h \
    micd_data_type.h \
    micd_com_format.h \
    micd_com_mode.h \
    micd_interface_level.h \
    micd_port_name.h \
    micd_simple_tab.h \
    micd_description.h \
    micd_convention.h \
    micd_from_to.h \
    micd_enum.h \
    micd_cons_prod_if.h \
    micd_aircraft_signal_name.h

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

INCLUDEPATH += $$PWD/../../SQL_manager/sql_database_manager
DEPENDPATH += $$PWD/../../SQL_manager/sql_database_manager
