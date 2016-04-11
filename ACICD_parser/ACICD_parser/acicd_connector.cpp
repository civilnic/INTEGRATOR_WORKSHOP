#include "acicd_connector.h"

acicd_connector::acicd_connector(sql_database_manager *database_manager) : acicd_element (database_manager)
{

    DB_FIELDS= { { 2, "Type" },
                 { 3, "Connector_name" }
               };

    DB_table_name="CONNECTOR";
    test_field="Connector_name";

    insert_query=QString("INSERT INTO %1 VALUES(NULL,NULL,NULL,:Type,:Connector_name)").arg(DB_table_name);
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query="CREATE TABLE IF NOT EXISTS [CONNECTOR](\
            [id] INTEGER CONSTRAINT [pk_CONNECTOR] NOT NULL PRIMARY KEY  AUTOINCREMENT,\
            [Equipment] INTEGER NULL,\
            [ACICD] INTEGER NULL,\
            [Type] VARCHAR( 45 ) NULL,\
            [Connector_name] VARCHAR( 45 ) NULL,\
                CONSTRAINT [Equipment]\
                    FOREIGN KEY([Equipment])\
                    REFERENCES [EQUIPMENT] ( [id] ),\
                CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [id] )\
            );";

    database_manager->create_table(create_table_query);

}
