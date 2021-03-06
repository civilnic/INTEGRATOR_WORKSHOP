#include "acicd_a429_signal_type.h"

acicd_a429_signal_type::acicd_a429_signal_type(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 38, "Name" },
               };

    DB_table_name="A429_SIGNAL_TYPE";
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
