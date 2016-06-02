#include "acicd_a429_signal_opaque_charact.h"

acicd_a429_signal_opaque_charact::acicd_a429_signal_opaque_charact(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 75, "size" },
                 { 76, "length" }
               };

    DB_table_name="A429_SIGNAL_OPAQUE_DESC";
    test_field="rowid";

    insert_query=QString("INSERT INTO %1 VALUES(:size,:length)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (size=:size) AND (length=:length);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [size] VARCHAR( 45 ) CHECK (size != ''),\
                [length] VARCHAR( 45 ) CHECK (length != ''),\
                CONSTRAINT unique_combinaison PRIMARY KEY (size, length) ON CONFLICT IGNORE\
                );\n\
            ").arg(DB_table_name);


    database_manager->create_table(create_table_query);
}
