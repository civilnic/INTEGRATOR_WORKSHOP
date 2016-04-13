#include "acicd_afdx_vl.h"

acicd_afdx_VL::acicd_afdx_VL(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 8, "VL_Identifier" },
                 { 9, "VL_name" },
                 { 11, "BAG" },
                 { 12, "MAX_frame_size" },
                 { 13, "Sub_VL_Number" },
                 { 14, "Sub_VL_Identifier" },
               };

    DB_table_name="AFDX_VL";
    test_field="VL_name";

    insert_query=QString("INSERT INTO %1 VALUES(NULL,:VL_name,:VL_Identifier,:BAG,:MAX_frame_size,:Sub_VL_Number,:Sub_VL_Identifier,NULL,NULL,:IC_active,:Skew_max)").arg(DB_table_name);
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [id] INTEGER CONSTRAINT [pk_%1] NOT NULL PRIMARY KEY AUTOINCREMENT,\
                [VL_name] VARCHAR( 45 ) NULL,\
                [VL_Identifier] INTEGER NULL,\
                [BAG] INTEGER NULL,\
                [MAX_frame_size] INTEGER NULL,\
                [Sub_VL_Number] INTEGER NULL,\
                [Sub_VL_Identifier] INTEGER NULL,\
                [EQUIPMENT] INTEGER NULL,\
                [ACICD] INTEGER NULL,\
                [IC_active] BIT NULL,\
                [Skew_max] INTEGER NULL,\
                     CONSTRAINT [EQUIPMENT]\
                         FOREIGN KEY([EQUIPMENT])\
                         REFERENCES [EQUIPMENT] ( [id] ),\
                     CONSTRAINT [ACICD]\
                         FOREIGN KEY([ACICD])\
                         REFERENCES [ACICD] ( [id] )\
            );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
