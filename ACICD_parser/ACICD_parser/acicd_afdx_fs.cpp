#include "acicd_afdx_fs.h"

acicd_afdx_FS::acicd_afdx_FS(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 21, "Name" },
                 { 22, "description" },
                 { 23, "adress_in_message" }
               };

    DB_table_name="AFDX_FS";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name,:description,:adress_in_message,:AFDX_FDS,:AFDX_MESSAGE,:AFDX_VL,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query=QString("\
               CREATE TABLE IF NOT EXISTS  [%1](\
                [Name] VARCHAR( 45 ) NOT NULL,\
                [description] VARCHAR( 45 ) NULL,\
                [adress_in_message] INTEGER NULL,\
                [AFDX_FDS] INTEGER NULL,\
                [AFDX_MESSAGE] INTEGER NULL,\
                [AFDX_VL] INTEGER NULL,\
                [ACICD] INTEGER NULL,\
                 CONSTRAINT unique_combinaison PRIMARY KEY (Name,ACICD) ON CONFLICT IGNORE,\
                 CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [rowid] ),\
                 CONSTRAINT [AFDX_MESSAGE]\
                    FOREIGN KEY([AFDX_MESSAGE])\
                    REFERENCES [AFDX_MESSAGE] ( [rowid] ),\
                 CONSTRAINT [AFDX_FDS]\
                    FOREIGN KEY([AFDX_FDS])\
                    REFERENCES [AFDX_FDS] ( [rowid] ),\
                 CONSTRAINT [AFDX_VL]\
                    FOREIGN KEY([AFDX_VL])\
                    REFERENCES [AFDX_VL] ( [rowid] )\
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
