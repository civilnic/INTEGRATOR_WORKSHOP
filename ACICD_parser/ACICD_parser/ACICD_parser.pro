TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    ../../CSV/csv_common.h \
    ../../CSV/csv_data.h \
    ../../CSV/csv_parser.h \
    ../../CSV/csv_stl_traits.h

INCLUDEPATH += ../../CSV/ \
               C:\local\boost_1_60_0
