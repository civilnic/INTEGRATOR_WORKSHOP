#include "acicd_discret_signal.h"

acicd_discret_signal::acicd_discret_signal(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 21, "Name" },
                 { 22, "description" },
                 { 23, "IO_type" },
                 { 24, "elec_accuracy" },
                 { 25, "scale_factor" },
                 { 26, "offset" },
                 { 27, "min" },
                 { 28, "max" },
                 { 29, "unit" },
                 { 30, "elec_coding_min" },
                 { 31, "elec_coding_max" },
                 { 32, "elec_coding_unit" },
                 { 33, "frequency" },
                 { 34, "I_min" },
                 { 35, "I_max" },
                 { 36, "I_unit" },
                 { 37, "V_min" },
                 { 38, "V_max" },
                 { 39, "V_unit" },
                 { 40, "function" }
               };

    DB_table_name="DISCRET_SIGNAL";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name,:description,:IO_type,:elec_accuracy,:scale_factor,:offset,:type,:min,:max,:unit,:elec_coding_min,:elec_coding_max,:elec_coding_unit,:frequency,:I_min,:I_max,:I_unit,:V_min,:V_max,:V_unit,:function,:ANA_PARAMETER,:ANA_LINE,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [Name] VARCHAR( 45 )  CHECK (Name != ''),\
                [description] VARCHAR( 45 ) NULL,\
                [IO_type] VARCHAR( 45 ) NULL,\
                [elec_accuracy] INTEGER NULL,\
                [scale_factor] VARCHAR( 45 ) NULL,\
                [offset] VARCHAR( 45 ) NULL,\
                [type] INTEGER NULL,\
                [min] INTEGER NULL,\
                [max] VARCHAR( 45 ) NULL,\
                [unit] VARCHAR( 45 ) NULL,\
                [elec_coding_min] VARCHAR( 45 ) NULL,\
                [elec_coding_max] VARCHAR( 45 ) NULL,\
                [elec_coding_unit] VARCHAR( 45 ) NULL,\
                [frequency] VARCHAR( 45 ) NULL,\
                [I_min] NUMERIC NULL,\
                [I_max] NUMERIC NULL,\
                [I_unit] VARCHAR( 10 ) NULL,\
                [V_min] NUMERIC NULL,\
                [V_max] NUMERIC NULL,\
                [V_unit] VARCHAR( 10 ) NULL,\
                [function] VARCHAR( 10 ) NULL,\
                [ANA_PARAMETER] INTEGER NULL,\
                [ANA_LINE] INTEGER NULL,\
                [ACICD] INTEGER NULL,\
                 CONSTRAINT unique_combinaison PRIMARY KEY (Name,ACICD) ON CONFLICT IGNORE,\
                 CONSTRAINT [type]\
                    FOREIGN KEY([type])\
                    REFERENCES [DATA_TYPE] ( [rowid] ),\
                 CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [rowid] ),\
                CONSTRAINT [ANA_PARAMETER]\
                   FOREIGN KEY([ANA_PARAMETER])\
                   REFERENCES [ANA_PARAMETER] ( [rowid] ),\
                 CONSTRAINT [ANA_LINE]\
                    FOREIGN KEY([ANA_LINE])\
                    REFERENCES [ANA_LINE] ( [rowid] )\
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
