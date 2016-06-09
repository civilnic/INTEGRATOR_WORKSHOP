#ifndef ACICD_DOCUMENT_H
#define ACICD_DOCUMENT_H

#include <string>
#include <fstream>
#include <iostream>
#include <map>

#include <QSqlDatabase>
#include <QtSql>
#include <regex>

#include "acicd_header.h"

#include "acicd_equipment.h"

#include "acicd_connector.h"
#include "acicd_connection_name.h"
#include "acicd_connector_line_type.h"
#include "acicd_connector_pin.h"
#include "acicd_connector_pin_role.h"

#include "acicd_afdx_tx_port.h"
#include "acicd_afdx_rx_port.h"
#include "acicd_afdx_port_type.h"
#include "acicd_afdx_port_characteristic.h"
#include "acicd_afdx_port_transmission_type.h"
#include "acicd_afdx_vl.h"
#include "acicd_afdx_message.h"
#include "acicd_afdx_message_type.h"
#include "acicd_application.h"

#include "acicd_afdx_fds.h"
#include "acicd_afdx_fs.h"
#include "acicd_afdx_parameter.h"
#include "acicd_data_type.h"
#include "acicd_keyword.h"
#include "acicd_afdx_signal.h"
#include "acicd_afdx_signal_bool_charact.h"
#include "acicd_afdx_signal_type.h"
#include "acicd_afdx_signal_enumerate_charact.h"
#include "acicd_afdx_signal_float_charact.h"
#include "acicd_afdx_signal_int_charact.h"
#include "acicd_afdx_signal_opaque_charact.h"
#include "acicd_afdx_signal_string_charact.h"
#include "acicd_unit.h"

#include "acicd_a429_bus.h"
#include "acicd_a429_label.h"
#include "acicd_a429_signal.h"
#include "acicd_a429_label_type.h"
#include "acicd_a429_parameter.h"
#include "acicd_a429_signal_bool_charact.h"
#include "acicd_a429_signal_enumerate_charact.h"
#include "acicd_a429_signal_float_charact.h"
#include "acicd_a429_signal_int_charact.h"
#include "acicd_a429_signal_opaque_charact.h"
#include "acicd_a429_signal_string_charact.h"
#include "acicd_a429_signal_type.h"

#include "acicd_ana_line.h"
#include "acicd_ana_signal.h"
#include "acicd_ana_parameter.h"

#include "acicd_discret_line.h"
#include "acicd_discret_signal.h"
#include "acicd_discret_parameter.h"

#include "acicd_description.h"

#include "sql_database_manager.h"



class ACICD_DOCUMENT
{
public:
    ACICD_DOCUMENT(sql_database_manager *database_manager,QString path_name);
    bool parse_ACICD(void);

    std::map<int,QString> DB_FIELDS_ACICD;
    std::map<QString,QString> DB_VALUES_ACICD;

    int insert_acicd(void);
    int set_equipment_reference(int equipment_id);
    bool create_acicd_table(void);
    int is_acicd_exist(QString Name);
    bool delete_acicd(int id);

private:
    int id;
    QString path_name;
    QSqlDatabase *db;
    sql_database_manager *BDD;

    const QString insert_query="INSERT INTO ACICD VALUES(:Name,:Path,:Micd,:Equipment,:Version)";
    const QString update_equipment_query="UPDATE ACICD SET Equipment = :Equipment WHERE (rowid=:rowid)";

};

const QString DB_QUERY_CREATE_ACICD="CREATE TABLE IF NOT EXISTS [ACICD](\
 [Name] VARCHAR( 45 ) NOT NULL,\
 [Path] VARCHAR( 45 ) NULL,\
 [Micd] INTEGER NULL,\
 [Equipment] INTEGER NULL,\
 [Version] VARCHAR( 5 ) NULL,\
    CONSTRAINT unique_combinaison PRIMARY KEY (Name) ON CONFLICT IGNORE,\
    CONSTRAINT [Equipment]\
        FOREIGN KEY([Equipment])\
        REFERENCES [EQUIPMENT] ( [rowid] ));\n";

#endif //ACICD_DOCUMENT_H
