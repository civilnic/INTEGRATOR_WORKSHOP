#include "acicd_a429_parameter.h"

acicd_a429_parameter::acicd_a429_parameter(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 33, "Name" },
                 { 28, "local_name" },
                 { 29, "local_name_not_produced" },
                 { 30, "refresh_period" },
                 { 31, "fonctionnal_attribute" },
                 { 32, "name_description" },
                 { 35, "description" },
                 { 36, "ref_doc" }
               };

            DB_table_name="A429_PARAMETER";
            test_field="Name";

            insert_query=QString("INSERT INTO %1 VALUES(:Name,:local_name,:local_name_not_used,:refresh_period,:fonctionnal_attribute,:name_description,:keyword,:description,:ref_doc,:type,:A429_LABEL,:A429_BUS,:ACICD)").arg(DB_table_name);
            test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name) AND (ACICD=:ACICD);").arg(DB_table_name);

            create_table_query=QString("\
                       CREATE TABLE  IF NOT EXISTS [%1](\
                        [Name] VARCHAR( 45 ) NULL,\
                        [local_name] VARCHAR( 45 ) NULL,\
                        [local_name_not_used] VARCHAR( 45 ) NULL,\
                        [refresh_period] INTEGER NULL,\
                        [fonctionnal_attribute] VARCHAR( 45 ) NULL,\
                        [name_description] VARCHAR( 45 ) NULL,\
                        [keyword] INTEGER NULL,\
                        [description] VARCHAR( 45 ) NULL,\
                        [ref_doc] VARCHAR( 45 ) NULL,\
                        [type] INTEGER NULL,\
                        [A429_LABEL] INTEGER NULL,\
                        [A429_BUS] INTEGER NULL,\
                        [ACICD] INTEGER NULL,\
                         CONSTRAINT unique_combinaison PRIMARY KEY (Name,ACICD) ON CONFLICT IGNORE,\
                         CONSTRAINT [type]\
                            FOREIGN KEY([type])\
                            REFERENCES [DATA_TYPE] ( [rowid] ),\
                         CONSTRAINT [KEYWORD]\
                            FOREIGN KEY([KEYWORD])\
                            REFERENCES [KEYWORD] ( [rowid] ),\
                         CONSTRAINT [ACICD]\
                            FOREIGN KEY([ACICD])\
                            REFERENCES [ACICD] ( [rowid] ),\
                         CONSTRAINT [A429_LABEL]\
                            FOREIGN KEY([A429_LABEL])\
                            REFERENCES [A429_LABEL] ( [rowid] ),\
                         CONSTRAINT [A429_BUS]\
                            FOREIGN KEY([A429_BUS])\
                            REFERENCES [A429_BUS] ( [rowid] )\
                        );\n\
                    ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
