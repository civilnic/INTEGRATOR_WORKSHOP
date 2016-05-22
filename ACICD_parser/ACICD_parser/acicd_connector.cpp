#include "acicd_connector.h"

acicd_connector::acicd_connector(sql_database_manager *database_manager) : acicd_element (database_manager)
{

    DB_FIELDS= { { 2, "Type" },
                 { 3, "Connector_name" }
               };

    DB_table_name="CONNECTOR";
    test_field="Connector_name";

    insert_query=QString("INSERT INTO %1 VALUES(NULL,:ACICD,:Type,:Connector_name)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Connector_name=:Connector_name) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query="CREATE TABLE IF NOT EXISTS [CONNECTOR](\
            [Equipment] INTEGER NULL,\
            [ACICD] INTEGER NOT NULL,\
            [Type] VARCHAR( 45 ) NULL,\
            [Connector_name] VARCHAR( 45 ) NOT NULL,\
                CONSTRAINT unique_combinaison PRIMARY KEY (Connector_name, ACICD) ON CONFLICT IGNORE,\
                CONSTRAINT [Equipment]\
                    FOREIGN KEY([Equipment])\
                    REFERENCES [EQUIPMENT] ( [rowid] ),\
                CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [rowid] )\
            );";

    database_manager->create_table(create_table_query);

}
