#include "acicd_discret_parameter.h"

acicd_discret_parameter::acicd_discret_parameter(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 11, "Name" },
                 { 6, "local_name" },
                 { 7, "local_name_not_produced" },
                 { 8, "refresh_period" },
                 { 9, "fonctionnal_attribute" },
                 { 10, "name_description" },
                 { 12, "description" },
                 { 13, "ref_doc" }
               };

    DB_table_name="DISCRET_PARAMETER";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name,:local_name,:local_name_not_used,:refresh_period,:fonctionnal_attribute,:name_description,:keyword,:description,:ref_doc,:type,:DISCRET_LINE,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name) AND (local_name=:local_name) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [Name] VARCHAR( 45 )  CHECK (Name != ''),\
                [local_name] VARCHAR( 45 ) CHECK (Name != ''),\
                [local_name_not_used] VARCHAR( 45 ) NULL,\
                [refresh_period] INTEGER NULL,\
                [fonctionnal_attribute] VARCHAR( 45 ) NULL,\
                [name_description] VARCHAR( 45 ) NULL,\
                [keyword] INTEGER NULL,\
                [description] VARCHAR( 45 ) NULL,\
                [ref_doc] VARCHAR( 45 ) NULL,\
                [type] INTEGER NULL,\
                [DISCRET_LINE] INTEGER NULL,\
                [ACICD] INTEGER NULL,\
                 CONSTRAINT unique_combinaison PRIMARY KEY (Name,local_name,ACICD) ON CONFLICT IGNORE,\
                 CONSTRAINT [type]\
                    FOREIGN KEY([type])\
                    REFERENCES [DATA_TYPE] ( [rowid] ),\
                 CONSTRAINT [keyword]\
                    FOREIGN KEY([keyword])\
                    REFERENCES [KEYWORD] ( [rowid] ),\
                 CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [rowid] ),\
                 CONSTRAINT [DISCRET_LINE]\
                    FOREIGN KEY([DISCRET_LINE])\
                    REFERENCES [DISCRET_LINE] ( [rowid] )\
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
