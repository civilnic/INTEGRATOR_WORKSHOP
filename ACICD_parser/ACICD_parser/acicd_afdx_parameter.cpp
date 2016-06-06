#include "acicd_afdx_parameter.h"

acicd_afdx_parameter::acicd_afdx_parameter(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 30, "Name" },
                 { 25, "local_name" },
                 { 26, "local_name_not_used" },
                 { 27, "refresh_period" },
                 { 28, "fonctionnal_attribute" },
                 { 29, "name_description" },
                 { 32, "description" },
                 { 33, "ref_doc" }
               };

    DB_table_name="AFDX_PARAMETER";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name,:local_name,:local_name_not_used,:refresh_period,:fonctionnal_attribute,:name_description,:keyword,:description,:ref_doc,:type,:AFDX_FDS,:AFDX_MESSAGE,:AFDX_VL,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name) AND (local_name=:local_name) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query=QString("\
               CREATE TABLE  IF NOT EXISTS [%1](\
                [Name] VARCHAR( 45 )  CHECK (Name != ''),\
                [local_name] VARCHAR( 45 )  CHECK (Name != ''),\
                [local_name_not_produced] VARCHAR( 45 ) NULL,\
                [refresh_period] INTEGER NULL,\
                [fonctionnal_attribute] VARCHAR( 45 ) NULL,\
                [name_description] VARCHAR( 45 ) NULL,\
                [keyword] INTEGER NULL,\
                [description] VARCHAR( 45 ) NULL,\
                [ref_doc] VARCHAR( 45 ) NULL,\
                [type] INTEGER NULL,\
                [AFDX_FDS] INTEGER NULL,\
                [AFDX_MESSAGE] INTEGER NULL,\
                [AFDX_VL] INTEGER NULL,\
                [ACICD] INTEGER NULL,\
                 CONSTRAINT unique_combinaison PRIMARY KEY (Name,local_name,ACICD) ON CONFLICT IGNORE,\
                 CONSTRAINT [type]\
                    FOREIGN KEY([type])\
                    REFERENCES [DATA_TYPE] ( [rowid] ),\
                 CONSTRAINT [KEYWORD]\
                    FOREIGN KEY([KEYWORD])\
                    REFERENCES [KEYWORD] ( [rowid] ),\
                 CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [rowid] ),\
                 CONSTRAINT [AFDX_FDS]\
                    FOREIGN KEY([AFDX_FDS])\
                    REFERENCES [AFDX_FDS] ( [rowid] ),\
                 CONSTRAINT [AFDX_MESSAGE]\
                    FOREIGN KEY([AFDX_MESSAGE])\
                    REFERENCES [AFDX_MESSAGE] ( [rowid] ),\
                 CONSTRAINT [AFDX_VL]\
                    FOREIGN KEY([AFDX_VL])\
                    REFERENCES [AFDX_VL] ( [rowid] )\
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
