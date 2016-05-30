#include "acicd_afdx_vl.h"

acicd_afdx_VL::acicd_afdx_VL(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 8, "VL_Identifier" },
                 { 9, "VL_name" },
                 { 11, "BAG" },
                 { 12, "MAX_frame_size" }
               };

    DB_table_name="AFDX_VL";
    test_field="VL_name";

    insert_query=QString("INSERT INTO %1 VALUES(:VL_name,:VL_Identifier,:BAG,:MAX_frame_size,:Sub_VL_Number,:Sub_VL_Identifier,NULL,NULL,:ACICD,:IC_active,:Skew_max)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (VL_name=:VL_name) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [VL_name] VARCHAR( 45 ) NOT NULL,\
                [VL_Identifier] INTEGER NOT NULL,\
                [BAG] INTEGER NULL,\
                [MAX_frame_size] INTEGER NULL,\
                [Sub_VL_Number] INTEGER NULL,\
                [Sub_VL_Identifier] INTEGER NULL,\
                [Connector_pin] INTEGER NULL,\
                [EQUIPMENT] INTEGER NULL,\
                [ACICD] INTEGER NOT NULL,\
                [IC_active] BIT NULL,\
                [Skew_max] INTEGER NULL,\
                     CONSTRAINT unique_combinaison PRIMARY KEY (VL_name,ACICD) ON CONFLICT IGNORE,\
                     CONSTRAINT [Connector_pin]\
                         FOREIGN KEY([Connector_pin])\
                         REFERENCES [CONNECTOR_PIN] ( [rowid] ),\
                     CONSTRAINT [EQUIPMENT]\
                         FOREIGN KEY([EQUIPMENT])\
                         REFERENCES [EQUIPMENT] ( [rowid] ),\
                     CONSTRAINT [ACICD]\
                         FOREIGN KEY([ACICD])\
                         REFERENCES [ACICD] ( [rowid] )\
            );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
