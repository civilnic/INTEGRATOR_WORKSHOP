#include "acicd_afdx_signal_opaque_charact.h"

acicd_afdx_signal_opaque_charact::acicd_afdx_signal_opaque_charact(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 60, "size" },
                 { 61, "length" },
                 { 62, "IOM_corresponding_label" }
               };

    DB_table_name="AFDX_SIGNAL_OPAQUE_DESC";
    test_field="rowid";

    insert_query=QString("INSERT INTO %1 VALUES(:size,:length,:IOM_corresponding_label)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (size=:size) AND (length=:length);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [size] VARCHAR( 45 ) CHECK (size != ''),\
                [length] VARCHAR( 45 ) CHECK (length != ''),\
                [IOM_corresponding_label] VARCHAR( 45 ) NULL,\
                CONSTRAINT unique_combinaison PRIMARY KEY (size, length) ON CONFLICT IGNORE\
                );\n\
            ").arg(DB_table_name);


    database_manager->create_table(create_table_query);
}
