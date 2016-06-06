#include "acicd_ana_line.h"

acicd_ANA_line::acicd_ANA_line(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 2, "Name" },
                 { 3, "description" },
                 { 4, "EMC_protection" }
               };

    DB_table_name="ANA_LINE";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name,:description,:EMC_protection,:CONNECTOR_PIN,:EQUIPMENT,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [Name] VARCHAR( 45 ) CHECK (Name != ''), \
                [description] VARCHAR( 45 ) NULL, \
                [EMC_protection] VARCHAR( 45 ) NULL, \
                [CONNECTOR_PIN] INTEGER NULL, \
                [EQUIPMENT] INTEGER NULL, \
                [ACICD] INTEGER NULL, \
                 CONSTRAINT unique_combinaison PRIMARY KEY (Name,ACICD) ON CONFLICT IGNORE,\
                 CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [rowid] ),\
                CONSTRAINT [EQUIPMENT]\
                    FOREIGN KEY([EQUIPMENT])\
                    REFERENCES [EQUIPMENT] ( [rowid] ),\
                 CONSTRAINT [CONNECTOR_PIN] \
                    FOREIGN KEY([CONNECTOR_PIN]) \
                    REFERENCES [CONNECTOR_PIN] ( [rowid] ) \
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}

