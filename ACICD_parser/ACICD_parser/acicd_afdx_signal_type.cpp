
#include "acicd_afdx_signal_type.h"

acicd_afdx_signal_type::acicd_afdx_signal_type(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 35, "Name" },
               };

    DB_table_name="AFDX_SIGNAL_TYPE";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(NULL,:Name)").arg(DB_table_name);
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query=QString("\
       CREATE TABLE IF NOT EXISTS [%1](\
        [id] INTEGER CONSTRAINT [pk_%1] NOT NULL PRIMARY KEY  AUTOINCREMENT,  \
        [Name] VARCHAR( 15 ) NULL\
       );\n\
       ").arg(DB_table_name);

     database_manager->create_table(create_table_query);
}
