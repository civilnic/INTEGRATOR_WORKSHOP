#include "acicd_a429_signal_enumerate_charact.h"

acicd_a429_signal_enumerate_charact::acicd_a429_signal_enumerate_charact(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 53, "state" },
                 { 54, "value" }
               };

    DB_table_name="A429_SIGNAL_ENUMERATE_DESC";
    test_field="rowid";

    insert_query=QString("INSERT INTO %1 VALUES(:state,:value)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (state=:state) AND (value=:value);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [state] VARCHAR( 45 ) CHECK (state != ''),\
                [value] VARCHAR( 45 ) CHECK (value != ''),\
                CONSTRAINT unique_combinaison PRIMARY KEY (state, value) ON CONFLICT IGNORE\
                );\n\
            ").arg(DB_table_name);


    database_manager->create_table(create_table_query);
}
