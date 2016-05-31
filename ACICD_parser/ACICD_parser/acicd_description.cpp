#include "acicd_description.h"

acicd_description::acicd_description(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 8, "Name" },
                 { 17, "Name" },
                 { 22, "Name" },
                 { 29, "Name" },
                 { 32, "Name" },
                 { 36, "Name" },
               };

    DB_table_name="DESCRIPTIONS";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name);").arg(DB_table_name);

    create_table_query=QString("\
       CREATE TABLE IF NOT EXISTS [%1](\
        [Name] VARCHAR( 80 ) NULL,\
            CONSTRAINT unique_combinaison PRIMARY KEY (Name) ON CONFLICT IGNORE\
       );\n\
       ").arg(DB_table_name);

     database_manager->create_table(create_table_query);
}
