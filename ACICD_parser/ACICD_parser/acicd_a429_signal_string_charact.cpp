#include "acicd_a429_signal_string_charact.h"

acicd_a429_signal_string_charact::acicd_a429_signal_string_charact(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 51, "length" },
                 { 52, "format" }
               };

    DB_table_name="A429_SIGNAL_STRING_DESC";
    test_field="rowid";

    insert_query=QString("INSERT INTO %1 VALUES(:length,:format)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (length=:length) AND (format=:format);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [length] VARCHAR( 45 ) CHECK (length != ''),\
                [format] VARCHAR( 45 ) CHECK (format != ''),\
                CONSTRAINT unique_combinaison PRIMARY KEY (length, format) ON CONFLICT IGNORE\
                );\n\
            ").arg(DB_table_name);


    database_manager->create_table(create_table_query);

}

