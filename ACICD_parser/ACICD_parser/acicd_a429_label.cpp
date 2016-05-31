#include "acicd_a429_label.h"

acicd_a429_label::acicd_a429_label(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 6, "Name" },
                 { 7, "number" },
                 { 9, "frequency" },
                 { 10, "cycle_frequency" },
                 { 11, "description" },
                 { 12, "type" },
                 { 13, "SDI" },
                 { 14, "SDI_00" },
                 { 15, "SDI_01" },
                 { 16, "SDI_10" },
                 { 17, "SDI_11" },
                 { 18, "SSM_lenght" },
                 { 19, "SSM_00" },
                 { 20, "SSM_01" },
                 { 21, "SSM_10" },
                 { 22, "SSM_11" },
                 { 25, "bit29_0" },
                 { 26, "bit29_1" }
               };

    DB_table_name="A429_LABEL";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name,:APPLICATION,:number,:frequency,:cycle_frequency,:description,:type,:SDI,:SDI_00,:SDI_01,:SDI_10,:SDI_11,:SSM_lenght,:SSM_00,:SSM_01,:SSM_10,:SSM_11,:bit29_0,:bit29_1,NULL,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query=QString("\
       CREATE TABLE IF NOT EXISTS [%1](\
        [Name] VARCHAR( 45 ) NULL,\
        [APPLICATION] INTEGER NULL,\
        [number] INTEGER NOT NULL,\
        [frequency] NUMERIC NULL,\
        [cycle_frequency] NUMERIC NULL,\
        [description] VARCHAR( 45 ) NULL,\
        [type] INTEGER NULL,\
        [SDI] VARCHAR( 45 ) NULL,\
        [SDI_00] VARCHAR( 45 ) NULL,\
        [SDI_01] VARCHAR( 45 ) NULL,\
        [SDI_10] VARCHAR( 45 ) NULL,\
        [SDI_11] VARCHAR( 45 ) NULL,\
        [SSM_lenght] INTEGER NOT NULL,\
        [SSM_00] VARCHAR( 45 ) NULL,\
        [SSM_01] VARCHAR( 45 ) NULL,\
        [SSM_10] VARCHAR( 45 ) NULL,\
        [SSM_11] VARCHAR( 45 ) NULL,\
        [bit29_0] VARCHAR( 45 ) NULL,\
        [bit29_1] VARCHAR( 45 ) NULL,\
        [A429_BUS] INTEGER NULL,\
        [ACICD] INTEGER NOT NULL,\
                CONSTRAINT unique_combinaison PRIMARY KEY (Name,ACICD) ON CONFLICT IGNORE,\
                CONSTRAINT [APPLICATION]\
                       FOREIGN KEY([APPLICATION])\
                       REFERENCES [APPLICATION] ( [rowid] ),\
                CONSTRAINT [ACICD]\
                       FOREIGN KEY([ACICD])\
                       REFERENCES [ACICD] ( [rowid] ),\
                CONSTRAINT [A429_BUS]\
                       FOREIGN KEY([A429_BUS])\
                       REFERENCES [A429_BUS] ( [rowid] ),\
                CONSTRAINT [type]\
                       FOREIGN KEY([type])\
                       REFERENCES [A429_LABEL_TYPE] ( [rowid] )\
       );\n\
       ").arg(DB_table_name);

     database_manager->create_table(create_table_query);
}
