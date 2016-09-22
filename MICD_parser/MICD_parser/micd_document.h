#ifndef MICD_DOCUMENT_H
#define MICD_DOCUMENT_H


#include <iostream>
#include <xls.h>
#include <boost/algorithm/string.hpp>

#include "sql_database_manager.h"



#include "micd_com_format.h"
#include "micd_com_mode.h"
#include "micd_data_type.h"
#include "micd_interface_level.h"
#include "micd_port_in.h"
#include "micd_port_out.h"
#include "micd_unit.h"


using namespace std;
using namespace xls;

class micd_document
{
public:
    micd_document(sql_database_manager *database_manager, const char * filename);
    bool parse_MICD(void);

    std::map<int,QString> DB_FIELDS;
    std::map<QString,QString> DB_VALUES;

    int insert_micd(void);

    bool create_micd_table(void);
    int is_micd_exist(QString Name);
    bool delete_micd(int id);

private:
    int id_micd;
    QString path_name;
    QSqlDatabase *db;
    sql_database_manager *BDD;

    const QString insert_query="INSERT INTO MICD VALUES(:Name,:Path,:Model,:Version)";

};

const QString DB_QUERY_CREATE_TABLE="CREATE TABLE IF NOT EXISTS [MICD](\
 [Name] TEXT NOT NULL,\
 [Path] TEXT NULL,\
 [Model] INTEGER NULL,\
 [Version] TEXT NULL,\
    CONSTRAINT unique_combinaison PRIMARY KEY (Name) ON CONFLICT IGNORE);\n";



#endif // MICD_DOCUMENT_H
