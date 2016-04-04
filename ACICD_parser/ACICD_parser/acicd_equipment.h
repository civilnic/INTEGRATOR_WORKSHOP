#ifndef ACICD_EQUIPMENT_H
#define ACICD_EQUIPMENT_H

#include <string>
#include <QString>
#include <map>
#include "sql_database_manager.h"

class acicd_equipment
{
public:
    acicd_equipment(sql_database_manager *database_manager);
    bool set_parameters(int field,std::string value);

    bool create_equipment_table(void);
    int insert_equipment(void);
    int is_equipment_exist(QString Name);

    QString get_name(void);
    int get_id(void);

    std::map<int,std::string> DB_FIELDS_EQUIPMENT= { { 2, "Name" },
                                                     { 3, "Description" },
                                                     { 4, "Type" },
                                                     { 5, "EMC_Protection" },
                                                     { 6, "Zone" },
                                                     { 7, "FIN" }
                                                   };
    std::map<QString,QString> DB_VALUES_EQUIPMENT;

private:
    int id;
    QSqlDatabase *db;
    sql_database_manager *BDD;

    QString insert_query="INSERT INTO EQUIPMENT VALUES(NULL,:Name,:Description,:Type,:EMC_Protection,:Zone,:FIN)";


};

const QString DB_QUERY_CREATE_EQUIPMENT="\
    CREATE TABLE IF NOT EXISTS [EQUIPMENT](      \
     [id] INTEGER CONSTRAINT [pk_EQUIPMENT] NOT NULL PRIMARY KEY AUTOINCREMENT,  \
     [Name] VARCHAR( 45 ) NULL,                                     \
     [Description] VARCHAR( 45 ) NULL,  \
     [Type] VARCHAR( 45 ) NULL,\
     [EMC_Protection] VARCHAR( 45 ) NULL,\
     [Zone] VARCHAR( 45 ) NULL,\
     [FIN] VARCHAR( 45 ) NULL\
    );\n\
";

#endif // ACICD_EQUIPMENT_H
