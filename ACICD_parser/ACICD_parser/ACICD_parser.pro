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
    acicd_connector_pin.cpp \
    acicd_afdx_tx_port.cpp \
    acicd_afdx_vl.cpp \
    acicd_afdx_message.cpp \
    acicd_afdx_rx_port.cpp \
    acicd_afdx_message_type.cpp \
    acicd_afdx_application.cpp \
    acicd_afdx_port_characteristic.cpp \
    acicd_afdx_port_type.cpp \
    acicd_afdx_port_transmission_type.cpp \
    acicd_afdx_fds.cpp \
    acicd_afdx_fs.cpp \
    acicd_afdx_signal.cpp \
    acicd_afdx_signal_type.cpp \
    acicd_afdx_coding_type.cpp \
    acicd_afdx_signal_bool_charact.cpp \
    acicd_afdx_signal_string_charact.cpp \
    acicd_afdx_signal_enumerate_charact.cpp \
    acicd_afdx_signal_float_charact.cpp \
    acicd_afdx_signal_int_charact.cpp \
    acicd_afdx_signal_opaque_charact.cpp \
    acicd_afdx_network.cpp \
    acicd_afdx_parameter.cpp \
    acicd_keyword.cpp \
    acicd_data_type.cpp \
    acicd_unit.cpp

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
    acicd_connector_pin.h \
    acicd_afdx_tx_port.h \
    acicd_afdx_vl.h \
    acicd_afdx_message.h \
    acicd_afdx_rx_port.h \
    acicd_afdx_message_type.h \
    acicd_afdx_application.h \
    acicd_afdx_port_characteristic.h \
    acicd_afdx_port_type.h \
    acicd_afdx_port_transmission_type.h \
    acicd_afdx_fds.h \
    acicd_afdx_fs.h \
    acicd_afdx_signal.h \
    acicd_afdx_signal_type.h \
    acicd_afdx_coding_type.h \
    acicd_afdx_signal_bool_charact.h \
    acicd_afdx_signal_string_charact.h \
    acicd_afdx_signal_enumerate_charact.h \
    acicd_afdx_signal_float_charact.h \
    acicd_afdx_signal_int_charact.h \
    acicd_afdx_signal_opaque_charact.h \
    acicd_afdx_network.h \
    acicd_afdx_parameter.h \
    acicd_keyword.h \
    acicd_data_type.h \
    acicd_unit.h

INCLUDEPATH += ../../CSV/ \
               C:\local\boost_1_60_0
