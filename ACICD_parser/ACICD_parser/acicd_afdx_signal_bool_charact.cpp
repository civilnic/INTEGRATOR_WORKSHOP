#include "acicd_afdx_signal_bool_charact.h"

acicd_afdx_signal_bool_charact::acicd_afdx_signal_bool_charact(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 7, "true_def" },
                 { 8, "false_def" },
                 { 9, "true_state" },
                 { 11, "false_state" },
                 { 12, "bool_logic" },
               };

    DB_table_name="AFDX_SIGNAL_BOOL_DESC";
    test_field="true_def";

    insert_query=QString("INSERT INTO %1 VALUES(NULL,:true_def,:false_def,:true_state,:false_state,:bool_logic,NULL)").arg(DB_table_name);
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [id] INTEGER CONSTRAINT [pk_%1] NOT NULL PRIMARY KEY AUTOINCREMENT,\
                [true_def] VARCHAR( 45 ) NULL,\
                [false_def] VARCHAR( 45 ) NULL,\
                [true_state] VARCHAR( 45 ) NULL,\
                [false_state] VARCHAR( 45 ) NULL,\
                [bool_logic] VARCHAR( 45 ) NULL\
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
