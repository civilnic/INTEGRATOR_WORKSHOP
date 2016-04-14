#include "acicd_afdx_message.h"

acicd_afdx_message::acicd_afdx_message(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 7, "Name" },
                 { 8, "description" },
                 { 9, "ref_doc" },
                 { 11, "Protocol_type" },
                 { 12, "Lenght" },
                 { 13, "Global_spare" },
                 { 14, "Transmission_rate" },
               };

    DB_table_name="AFDX_MESSAGE";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(NULL,:Name,:AFDX_APPLICATION,:AFDX_VL,:AFDX_TX_PORT,:ACICD,:description,:ref_doc,:type,:AFDX_MESSAGE_TYPE,:Protocol_type,:Lenght,:Global_spare,:Transmission_rate)").arg(DB_table_name);
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [id] INTEGER CONSTRAINT [pk_%1] NOT NULL PRIMARY KEY  AUTOINCREMENT,  \
                [Name] VARCHAR( 45 ) NULL,\
                [AFDX_APPLICATION] INTEGER NULL,\
                [AFDX_VL] INTEGER NULL,\
                [AFDX_TX_PORT] INTEGER NULL,\
                [ACICD] INTEGER NULL,\
                [description] VARCHAR( 45 ) NULL,\
                [ref_doc] VARCHAR( 45 ) NULL,\
                [type] VARCHAR( 45 ) NULL,\
                [AFDX_MESSAGE_TYPE] INTEGER NULL,\
                [Protocol_type] VARCHAR( 45 ) NULL,\
                [Lenght] INTEGER NULL,\
                [Global_spare] INTEGER NULL,\
                [Transmission_rate] INTEGER NULL,\
                 CONSTRAINT [AFDX_APPLICATION]\
                        FOREIGN KEY([AFDX_APPLICATION])\
                        REFERENCES [AFDX_APPLICATION] ( [id] ),\
                 CONSTRAINT [ACICD]\
                        FOREIGN KEY([ACICD])\
                        REFERENCES [ACICD] ( [id] ),\
                 CONSTRAINT [AFDX_VL]\
                        FOREIGN KEY([AFDX_VL])\
                        REFERENCES [AFDX_VL] ( [id] ),\
                 CONSTRAINT [AFDX_TX_PORT]\
                        FOREIGN KEY([AFDX_TX_PORT])\
                        REFERENCES [AFDX_TX_PORT] ( [id] ),\
                 CONSTRAINT [AFDX_MESSAGE_TYPE]\
                        FOREIGN KEY([AFDX_MESSAGE_TYPE])\
                        REFERENCES [AFDX_MESSAGE_TYPE] ( [id] )\
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
