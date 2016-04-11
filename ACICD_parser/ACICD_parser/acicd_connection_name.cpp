#include "acicd_connection_name.h"

acicd_connection_name::acicd_connection_name(sql_database_manager *database_manager) : acicd_element (database_manager)
{

    DB_FIELDS= { { 6, "Name" },
               };

    DB_table_name="CONNECTION_NAME";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(NULL,:Name)").arg(DB_table_name);
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query=QString("CREATE TABLE IF NOT EXISTS [%1](\
             [id] INTEGER CONSTRAINT [pk_%1] NOT NULL PRIMARY KEY AUTOINCREMENT,\
             [Name] VARCHAR( 45 ) NULL\
            );\n\
        ").arg(DB_table_name);

     database_manager->create_table(create_table_query);
}
