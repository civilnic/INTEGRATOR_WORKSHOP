#include "acicd_connector.h"

acicd_connector::acicd_connector(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    id=-1;
    BDD=database_manager;
    db=(*BDD).get_db();

    DB_FIELDS= { { 2, "Type" },
                 { 3, "Name" },
                 { 4, "Pin" },
                 { 5, "Pin_Role" },
                 { 6, "Connection_Name" },
                 { 7, "Line_Type" }
               };

    DB_table_name="CONNECTOR";
    test_field="Name";

    insert_query="INSERT INTO EQUIPMENT VALUES(NULL,:Name,:Description,:Type,:EMC_Protection,:Zone,:FIN)";
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query="\
            CREATE TABLE IF NOT EXISTS [CONNECTOR]([id] INTEGER CONSTRAINT [pk_CONNECTOR] NOT NULL PRIMARY KEY  AUTOINCREMENT,[Equipment] INTEGER NULL,[ACICD] INTEGER NULL,\n\
            [Type] VARCHAR( 45 ) NULL,\n\
            [Name] VARCHAR( 45 ) NULL,\n\
            [Pin] VARCHAR( 45 ) NULL,\n\
            [Pin_Role] INTEGER NULL,\n\
            [Connection_Name] INTEGER NULL,\n\
            [Line_Type] INTEGER NULL,\n\
            [Speed] INTEGER NULL,\n\
            [NetworkId] VARCHAR( 3 ) NULL,\n\
            CONSTRAINT [Equipment]\n\
            FOREIGN KEY([Equipment])\n\
            REFERENCES [EQUIPMENT] ( [id] ),\n\
            CONSTRAINT [ACICD]\n\
            FOREIGN KEY([ACICD])\n\
            REFERENCES [ACICD] ( [id] ),\n\
            CONSTRAINT [Pin_Role]\n\
            FOREIGN KEY([Pin_Role])\n\
            REFERENCES [Connector_Pin_Role] ( [id] ),\n\
            CONSTRAINT [Line_Type]\n\
            FOREIGN KEY([Line_Type])\n\
            REFERENCES [Connector_Line_type] ( [id] ),\n\
            CONSTRAINT [Connection_Name]\n\
            FOREIGN KEY([Connection_Name])\n\
            REFERENCES [Connection_Name] ( [id] )\n\
            );\n\
            ";








}
