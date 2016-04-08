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

    const QString insert_query="INSERT INTO ACICD VALUES(NULL,:Name,:Path,:Micd,:Equipment,:Version)";
    const QString update_equipment_query="UPDATE ACICD SET Equipment = :Equipment WHERE (id=:id)";

};

const QString DB_QUERY_CREATE_ACICD="CREATE TABLE IF NOT EXISTS [ACICD](\
 [id] INTEGER CONSTRAINT [pk_ACICD] NOT NULL PRIMARY KEY AUTOINCREMENT,\
 [Name] VARCHAR( 45 ) NOT NULL,\
 [Path] VARCHAR( 45 ) NULL,\
 [Micd] INTEGER NULL,\
 [Equipment] INTEGER NULL,\
 [Version] VARCHAR( 5 ) NULL,\
  CONSTRAINT [Equipment]\
  FOREIGN KEY([Equipment])\
    REFERENCES [EQUIPMENT] ( [id] ));\n";

#endif //ACICD_DOCUMENT_H
