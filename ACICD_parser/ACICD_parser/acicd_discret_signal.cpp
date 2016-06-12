#include "acicd_discret_signal.h"

acicd_discret_signal::acicd_discret_signal(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 17, "Name" },
                 { 18, "description" },
                 { 19, "IO_type" },
                 { 20, "true_state" },
                 { 21, "false_state" },
                 { 22, "unit" },
                 { 23, "logic" },
                 { 24, "stabilization_time" },
                 { 25, "default_value" },
                 { 26, "min" },
                 { 27, "max" },
                 { 28, "unit_current" },
                 { 29, "range" }
               };

    DB_table_name="DISCRET_SIGNAL";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name,:description,:IO_type,:true_state,:false_state,:unit,:logic,:stabilization_time,:default_value,:min,:max,:unit_current,:range,:DISCRET_PARAMETER,:DISCRET_LINE,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [Name] VARCHAR( 45 )  CHECK (Name != ''),\
                [description] VARCHAR( 45 ) NULL,\
                [IO_type] VARCHAR( 15 ) NULL,\
                [true_state] VARCHAR( 15 ) NULL,\
                [false_state] VARCHAR( 15 ) NULL,\
                [unit] VARCHAR( 5 ) NULL,\
                [logic] VARCHAR( 15 ) NULL,\
                [stabilization_time] INTEGER NULL,\
                [default_value] VARCHAR( 15 ) NULL,\
                [min] INTEGER NULL,\
                [max] INTEGER NULL,\
                [unit_current] VARCHAR( 15 ) NULL,\
                [range] VARCHAR( 45 ) NULL,\
                [DISCRET_PARAMETER] INTEGER NULL,\
                [DISCRET_LINE] INTEGER NULL,\
                [ACICD] INTEGER NULL,\
                 CONSTRAINT unique_combinaison PRIMARY KEY (Name,ACICD) ON CONFLICT IGNORE,\
                 CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [rowid] ),\
                CONSTRAINT [DISCRET_PARAMETER]\
                   FOREIGN KEY([DISCRET_PARAMETER])\
                   REFERENCES [DISCRET_PARAMETER] ( [rowid] ),\
                 CONSTRAINT [DISCRET_LINE]\
                    FOREIGN KEY([DISCRET_LINE])\
                    REFERENCES [DISCRET_LINE] ( [rowid] )\
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
