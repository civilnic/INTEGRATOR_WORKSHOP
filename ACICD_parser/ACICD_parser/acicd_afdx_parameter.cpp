#include "acicd_afdx_parameter.h"

acicd_afdx_parameter::acicd_afdx_parameter(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 30, "Name" },
                 { 25, "local_name" },
                 { 26, "local_name_not_produced" },
                 { 27, "refresh_period" },
                 { 28, "fonctionnal_attribute" },
                 { 29, "name_description" },
                 { 32, "description" },
                 { 33, "ref_doc" }
               };

    DB_table_name="AFDX_PARAMETER";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(NULL,:Name,:local_name,:local_name_not_produced,:refresh_period,:fonctionnal_attribute,:name_description,:keyword,:description,:ref_doc,:type,:AFDX_FDS,:AFDX_MESSAGE,:AFDX_VL,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query=QString("\
               CREATE TABLE [%1](\
                [id] INTEGER CONSTRAINT [pk_%1] NOT NULL PRIMARY KEY  AUTOINCREMENT,  \
                [Name] VARCHAR( 45 ) NULL,\
                [local_name] VARCHAR( 45 ) NULL,\
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
                CONSTRAINT [type]\
                    FOREIGN KEY([type])\
                    REFERENCES [DATA_TYPE] ( [id] ),\
                CONSTRAINT [KEYWORD]\
                    FOREIGN KEY([KEYWORD])\
                    REFERENCES [KEYWORD] ( [id] ),\
                 CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [id] ),\
                 CONSTRAINT [AFDX_FDS]\
                    FOREIGN KEY([AFDX_FDS])\
                    REFERENCES [AFDX_FDS] ( [id] ),\
                 CONSTRAINT [AFDX_MESSAGE]\
                    FOREIGN KEY([AFDX_MESSAGE])\
                    REFERENCES [AFDX_MESSAGE] ( [id] ),\
                 CONSTRAINT [AFDX_VL]\
                    FOREIGN KEY([AFDX_VL])\
                    REFERENCES [AFDX_VL] ( [id] )\
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}