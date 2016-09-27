#include "micd_simple_tab.h"

micd_simple_tab::micd_simple_tab(sql_database_manager *database_manager) : micd_element (database_manager)
{
    test_field="Name";

}


micd_simple_tab::init_table(sql_database_manager *database_manager)
{

    insert_query=QString("INSERT INTO %1 VALUES(:Name)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name);").arg(DB_table_name);

    create_table_query=QString("\
       CREATE TABLE IF NOT EXISTS [%1](\
        [Name] TEXT CHECK (Name != '') CHECK (Name NOT NULL),\
            CONSTRAINT unique_combinaison PRIMARY KEY (Name) ON CONFLICT IGNORE\
       );\n\
       ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}

