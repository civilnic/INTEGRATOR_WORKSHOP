#include "acicd_a429_bus.h"

acicd_a429_bus::acicd_a429_bus(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 2, "Name" },
                 { 3, "description" },
                 { 4, "EMC_protection" },
                 { 5, "Speed" },
                 { 6, "Parity_type" },
                 { 7, "transmission_rate" }
               };

    DB_table_name="A429_BUS";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name,:description,:EMC_protection,:Speed,:Parity_type,:transmission_rate,NULL,NULL,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name) AND (ACICD=:ACICD);").arg(DB_table_name);


    create_table_query=QString("\
       CREATE TABLE IF NOT EXISTS [%1](\
        [Name] VARCHAR( 45 ) NULL,\
        [description] VARCHAR( 45 ) NULL,\
        [EMC_protection] VARCHAR( 45 ) NULL,\
        [Speed] VARCHAR( 5 ) NULL,\
        [Parity_type] VARCHAR( 10 ) NULL,\
        [transmission_rate] NUMERIC NULL,\
        [Connector_pin] INTEGER NULL,\
        [EQUIPMENT] INTEGER NULL,\
        [ACICD] INTEGER NOT NULL,\
            CONSTRAINT unique_combinaison PRIMARY KEY (Name,ACICD) ON CONFLICT IGNORE,\
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
