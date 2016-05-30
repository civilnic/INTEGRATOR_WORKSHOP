#include "acicd_a429_signal.h"

acicd_a429_signal::acicd_a429_signal(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 2, "Name" },
                 { 3, "description" },
                 { 4, "type" },
               };

    DB_table_name="AFDX_APPLICATION";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name,:description,:type)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name);").arg(DB_table_name);

    create_table_query=QString("\
       CREATE TABLE IF NOT EXISTS [%1](\
        [Name] VARCHAR( 45 ) NULL,\
        [description] VARCHAR( 45 ) NULL,\
        [type] VARCHAR( 45 ) NULL,\
             CONSTRAINT unique_combinaison PRIMARY KEY (Name) ON CONFLICT IGNORE\
       );\n\
       ").arg(DB_table_name);

     database_manager->create_table(create_table_query);
}
