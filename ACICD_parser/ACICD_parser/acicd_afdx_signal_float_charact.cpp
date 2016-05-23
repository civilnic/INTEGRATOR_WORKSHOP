
#include "acicd_afdx_signal_float_charact.h"

acicd_afdx_signal_float_charact::acicd_afdx_signal_float_charact(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 41, "true_def" },
                 { 42, "false_def" },
                 { 43, "true_state" },
                 { 44, "false_state" },
                 { 45, "bool_logic" },
               };

    DB_table_name="AFDX_SIGNAL_BOOL_DESC";
    test_field="rowid";

    insert_query=QString("INSERT INTO %1 VALUES(:true_def,:false_def,:true_state,:false_state,:bool_logic)").arg(DB_table_name);
     test_query=QString("SELECT rowid FROM %1 WHERE (true_def=:true_def) AND (false_def=:false_def) AND (true_state=:true_state) AND (false_state=:false_state);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [min] VARCHAR( 45 ) NOT NULL,\
                [max] VARCHAR( 45 ) NOT NULL,\
                [true_state] VARCHAR( 45 ) NOT NULL,\
                [false_state] VARCHAR( 45 ) NOT NULL,\
                [bool_logic] VARCHAR( 45 ) NULL,\
                CONSTRAINT unique_combinaison PRIMARY KEY (true_def, false_def, true_state, false_state ) ON CONFLICT IGNORE\
                );\n\
            ").arg(DB_table_name);


    database_manager->create_table(create_table_query);
   // database_manager->execute_query(create_index_query);
}
