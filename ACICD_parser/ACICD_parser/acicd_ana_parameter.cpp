#include "acicd_ana_parameter.h"

acicd_ANA_parameter::acicd_ANA_parameter(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 12, "Name" },
                 { 7, "local_name" },
                 { 8, "local_name_not_produced" },
                 { 9, "refresh_period" },
                 { 10, "fonctionnal_attribute" },
                 { 11, "name_description" },
                 { 14, "description" },
                 { 15, "ref_doc" }
               };

    DB_table_name="ANA_PARAMETER";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name,:local_name,:local_name_not_used,:refresh_period,:fonctionnal_attribute,:name_description,:keyword,:description,:ref_doc,:type,:ANA_LINE,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [Name] VARCHAR( 45 )  CHECK (Name != ''),\
                [local_name] VARCHAR( 45 ) NULL,\
                [local_name_not_used] VARCHAR( 45 ) NULL,\
                [refresh_period] INTEGER NULL,\
                [fonctionnal_attribute] VARCHAR( 45 ) NULL,\
                [name_description] VARCHAR( 45 ) NULL,\
                [keyword] INTEGER NULL,\
                [description] VARCHAR( 45 ) NULL,\
                [ref_doc] VARCHAR( 45 ) NULL,\
                [type] INTEGER NULL,\
                [ANA_LINE] INTEGER NULL,\
                [ACICD] INTEGER NULL,\
                 CONSTRAINT unique_combinaison PRIMARY KEY (Name,ACICD) ON CONFLICT IGNORE,\
                 CONSTRAINT [type]\
                    FOREIGN KEY([type])\
                    REFERENCES [DATA_TYPE] ( [rowid] ),\
                 CONSTRAINT [keyword]\
                    FOREIGN KEY([keyword])\
                    REFERENCES [KEYWORD] ( [rowid] ),\
                 CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [rowid] ),\
                 CONSTRAINT [ANA_LINE]\
                    FOREIGN KEY([ANA_LINE])\
                    REFERENCES [ANA_LINE] ( [rowid] )\
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
