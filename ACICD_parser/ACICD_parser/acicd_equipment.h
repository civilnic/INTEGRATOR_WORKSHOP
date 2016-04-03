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
    QString get_name(void);
    QString insert_query;

    bool create_equipment_table(void);
    int insert_equipment(void);
    int is_equipment_exist(QString Name);

    std::map<int,std::string> DB_FIELDS_EQUIPMENT;
    std::map<QString,QString> DB_VALUES_EQUIPMENT;

private:
    int id;
    QSqlDatabase *db;
    sql_database_manager *BDD;
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
