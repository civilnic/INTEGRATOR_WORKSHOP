#include "acicd_afdx_fds.h"

acicd_afdx_FDS::acicd_afdx_FDS(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 16, "Name" },
                 { 17, "description" },
                 { 18, "lenght" },
                 { 19, "spare_lenght" },
                 { 20, "adress_in_message" },
               };

    DB_table_name="AFDX_FDS";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(NULL,:Name,:description,:lenght,:spare_lenght,:adress_in_message,:AFDX_FS,:AFDX_MESSAGE,:AFDX_VL,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query=QString("\
               CREATE TABLE [%1](\
                [id] INTEGER CONSTRAINT [pk_%1] NOT NULL PRIMARY KEY  AUTOINCREMENT,  \
                [Name] VARCHAR( 45 ) NULL,\
                [description] VARCHAR( 45 ) NULL,\
                [lenght] INTEGER NULL,\
                [spare_lenght] INTEGER NULL,\
                [adress_in_message] INTEGER NULL,\
                [AFDX_FS] INTEGER NULL,\
                [AFDX_MESSAGE] INTEGER NULL,\
                [AFDX_VL] INTEGER NULL,\
                [ACICD] INTEGER NULL,\
                 CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [id] ),\
                 CONSTRAINT [AFDX_MESSAGE]\
                    FOREIGN KEY([AFDX_MESSAGE])\
                    REFERENCES [AFDX_MESSAGE] ( [id] ),\
                 CONSTRAINT [AFDX_VL]\
                    FOREIGN KEY([AFDX_VL])\
                    REFERENCES [AFDX_VL] ( [id] ),\
                 CONSTRAINT [AFDX_FS]\
                    FOREIGN KEY([AFDX_FS])\
                    REFERENCES [AFDX_FS] ( [id] )\
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);

}
