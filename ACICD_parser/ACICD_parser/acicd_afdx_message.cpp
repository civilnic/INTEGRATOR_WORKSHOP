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

    insert_query=QString("INSERT INTO %1 VALUES(:Name,:APPLICATION,:AFDX_VL,:AFDX_TX_PORT,:AFDX_RX_PORT,:ACICD,:description,:ref_doc,:type,:AFDX_MESSAGE_TYPE,:Protocol_type,:Lenght,:Global_spare,:Transmission_rate)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [Name] VARCHAR( 45 ) NULL,\
                [APPLICATION] INTEGER NULL,\
                [AFDX_VL] INTEGER NULL,\
                [AFDX_TX_PORT] INTEGER NULL,\
                [AFDX_RX_PORT] INTEGER NULL,\
                [ACICD] INTEGER NOT NULL,\
                [description] VARCHAR( 45 ) NULL,\
                [ref_doc] VARCHAR( 45 ) NULL,\
                [type] VARCHAR( 45 ) NULL,\
                [AFDX_MESSAGE_TYPE] INTEGER NULL,\
                [Protocol_type] VARCHAR( 45 ) NULL,\
                [Lenght] INTEGER NULL,\
                [Global_spare] INTEGER NULL,\
                [Transmission_rate] INTEGER NULL,\
                 CONSTRAINT unique_combinaison PRIMARY KEY (Name,ACICD) ON CONFLICT IGNORE,\
                 CONSTRAINT [APPLICATION]\
                        FOREIGN KEY([APPLICATION])\
                        REFERENCES [APPLICATION] ( [rowid] ),\
                 CONSTRAINT [ACICD]\
                        FOREIGN KEY([ACICD])\
                        REFERENCES [ACICD] ( [rowid] ),\
                 CONSTRAINT [AFDX_VL]\
                        FOREIGN KEY([AFDX_VL])\
                        REFERENCES [AFDX_VL] ( [rowid] ),\
                 CONSTRAINT [AFDX_TX_PORT]\
                        FOREIGN KEY([AFDX_TX_PORT])\
                        REFERENCES [AFDX_TX_PORT] ( [rowid] ),\
                CONSTRAINT [AFDX_RX_PORT]\
                       FOREIGN KEY([AFDX_RX_PORT])\
                       REFERENCES [AFDX_RX_PORT] ( [rowid] ),\
                 CONSTRAINT [AFDX_MESSAGE_TYPE]\
                        FOREIGN KEY([AFDX_MESSAGE_TYPE])\
                        REFERENCES [AFDX_MESSAGE_TYPE] ( [rowid] )\
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
