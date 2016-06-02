#include "acicd_a429_signal_int_charact.h"

acicd_a429_signal_int_charact::acicd_a429_signal_int_charact(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 65, "min" },
                 { 66, "max" },
                 { 67, "unit" },
                 { 68, "accuracy" },
                 { 69, "coding_type" },
                 { 70, "resolution" },
                 { 71, "scale_factor" },
                 { 72, "offset" },
                 { 73, "signed" },
                 { 74, "non_linear_scale" }
               };

    DB_table_name="A429_SIGNAL_INT_DESC";
    test_field="rowid";

    insert_query=QString("INSERT INTO %1 VALUES(:min,:max,:unit,:accuracy,:coding_type)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (min=:min) AND (max=:max) AND (unit=:unit) AND (coding_type=:coding_type) AND (resolution=:resolution) AND (scale_factor=:scale_factor) AND (offset=:offset) AND (signed=:signed) AND (non_linear_scale=:non_linear_scale);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [min] NUMERIC CHECK (min != ''),\
                [max] NUMERIC CHECK (max != ''),\
                [unit]  VARCHAR( 10 ) CHECK (unit != ''),\
                [accuracy] VARCHAR( 20 ) NULL,\
                [coding_type] VARCHAR( 10 ) CHECK (coding_type != ''),\
                [resolution] NUMERIC CHECK (min != ''),\
                [scale_factor] NUMERIC NULL,\
                [offset]  VARCHAR( 10 ) NULL,\
                [signed] VARCHAR( 5 ) NULL,\
                [non_linear_scale] VARCHAR( 45 ) CHECK (coding_type != ''),\
                    CONSTRAINT unique_combinaison PRIMARY KEY (min, max, unit, coding_type,resolution,scale_factor,offset,signed,non_linear_scale) ON CONFLICT IGNORE,\
                    CONSTRAINT [unit]\
                        FOREIGN KEY([unit])\
                        REFERENCES [UNITS] ( [rowid] )\
                );\n\
            ").arg(DB_table_name);


    database_manager->create_table(create_table_query);
}
