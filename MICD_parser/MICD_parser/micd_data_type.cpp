#include "micd_data_type.h"

micd_data_type::micd_data_type(sql_database_manager *database_manager) : micd_element (database_manager)
{
    DB_FIELDS= { { 52, "Name" },
                 { 57, "Name" }
               };

    DB_table_name="UNITS";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name);").arg(DB_table_name);

    create_table_query=QString("\
       CREATE TABLE IF NOT EXISTS [%1](\
        [Name] VARCHAR( 15 ) CHECK (Name != ''),\
            CONSTRAINT unique_combinaison PRIMARY KEY (Name) ON CONFLICT IGNORE\
       );\n\
       ").arg(DB_table_name);

     database_manager->create_table(create_table_query);
}
