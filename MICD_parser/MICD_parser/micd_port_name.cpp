#include "micd_port_name.h"

micd_port_name::micd_port_name(sql_database_manager *database_manager) : micd_element (database_manager)
{
    DB_FIELDS= { { 0, "Name" }
               };

    DB_table_name="PORTS_NAME";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:MICD,:Name)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name);").arg(DB_table_name);

    create_table_query=QString("\
       CREATE TABLE IF NOT EXISTS [%1](\
        [MICD] INTEGER NULL,\
        [Name] TEXT CHECK (Name != ''),\
        CONSTRAINT unique_combinaison PRIMARY KEY (Name) ON CONFLICT IGNORE\
       );\n\
       ").arg(DB_table_name);

     database_manager->create_table(create_table_query);
}
