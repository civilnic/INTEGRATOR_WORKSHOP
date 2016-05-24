
#include "acicd_afdx_signal_float_charact.h"

acicd_afdx_signal_float_charact::acicd_afdx_signal_float_charact(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 50, "min" },
                 { 51, "max" },
               //  { 52, "unit" },
                 { 53, "accuracy" },
                 { 54, "coding_type" }
               };

    DB_table_name="AFDX_SIGNAL_FLOAT_DESC";
    test_field="rowid";

    insert_query=QString("INSERT INTO %1 VALUES(:min,:max,NULL,:accuracy,:coding_type)").arg(DB_table_name);
     test_query=QString("SELECT rowid FROM %1 WHERE (min=:min) AND (max=:max) AND (unit=:unit) AND (accuracy=:accuracy) AND (coding_type=:coding_type);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [min] VARCHAR( 45 ) NOT NULL,\
                [max] VARCHAR( 45 ) NOT NULL,\
                [unit] INTEGER NULL,\
                [accuracy] VARCHAR( 45 ) NULL,\
                [coding_type] VARCHAR( 45 ) NOT NULL,\
                    CONSTRAINT unique_combinaison PRIMARY KEY (min, max, unit, accuracy, coding_type) ON CONFLICT IGNORE,\
                    CONSTRAINT [unit]\
                        FOREIGN KEY([unit])\
                        REFERENCES [UNITS] ( [rowid] )\
                );\n\
            ").arg(DB_table_name);


    database_manager->create_table(create_table_query);

}
