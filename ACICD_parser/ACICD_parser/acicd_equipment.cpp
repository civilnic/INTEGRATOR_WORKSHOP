#include "acicd_equipment.h"

acicd_equipment::acicd_equipment(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 2, "Name" },
                 { 3, "Description" },
                 { 4, "Type" },
                 { 5, "EMC_Protection" },
                 { 6, "Zone" },
                 { 7, "FIN" }
               };

    DB_table_name="EQUIPMENT";
    test_field="Name";

    insert_query="INSERT INTO EQUIPMENT VALUES(NULL,:Name,:Description,:Type,:EMC_Protection,:Zone,:FIN,:ACICD)";
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query="\
            CREATE TABLE IF NOT EXISTS [EQUIPMENT](      \
             [id] INTEGER CONSTRAINT [pk_EQUIPMENT] NOT NULL PRIMARY KEY AUTOINCREMENT,  \
             [Name] VARCHAR( 45 ) NULL,                                     \
             [Description] VARCHAR( 45 ) NULL,  \
             [Type] VARCHAR( 45 ) NULL,\
             [EMC_Protection] VARCHAR( 45 ) NULL,\
             [Zone] VARCHAR( 45 ) NULL,\
             [FIN] VARCHAR( 45 ) NULL,\
             [ACICD] INTEGER NULL,\
              CONSTRAINT [ACICD]\
              FOREIGN KEY([ACICD])\
              REFERENCES [ACICD] ( [id] )\
            );\n\
        ";
     database_manager->create_table(create_table_query);
}


