#include "acicd_data_type.h"

acicd_data_type::acicd_data_type(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= {  { 24, "Name" }                     //FK
               };

    DB_table_name="DATA_TYPE";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name);").arg(DB_table_name);

    create_table_query=QString("\
       CREATE TABLE IF NOT EXISTS [%1](\
        [Name] VARCHAR( 45 ) NULL,\
                CONSTRAINT unique_combinaison PRIMARY KEY (Name) ON CONFLICT IGNORE\
       );\n\
       ").arg(DB_table_name);

     database_manager->create_table(create_table_query);
}
