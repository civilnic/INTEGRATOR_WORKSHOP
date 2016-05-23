#include "acicd_connector_pin.h"

acicd_connector_pin::acicd_connector_pin(sql_database_manager *database_manager) : acicd_element (database_manager)
{

    DB_FIELDS= { { 4, "Connector_pin" }
               };

    DB_table_name="CONNECTOR_PIN";
    test_field="Connector_pin";

    insert_query=QString("INSERT INTO %1 VALUES(:Connector_pin,:Connector_pin_role,:Connection_name,:Line_type,:Connector,:ACICD,:Physical_Id,:Physical_speed,:Network_id)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Connector_pin=:Connector_pin) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query="CREATE TABLE IF NOT EXISTS [CONNECTOR_PIN](\
            [Connector_pin] VARCHAR( 45 ) NOT NULL,\
            [Connector_pin_role] INTEGER NULL,\
            [Connection_name] INTEGER NULL,\
            [Line_type] INTEGER NULL,\
            [Connector] INTEGER NULL,\
            [ACICD] INTEGER NOT NULL,\
            [Physical_Id] VARCHAR( 45 ) NULL,\
            [Physical_speed] VARCHAR( 45 ) NULL,\
            [Network_id] VARCHAR( 45 ) NULL,\
                CONSTRAINT unique_combinaison PRIMARY KEY (Connector_pin,ACICD) ON CONFLICT IGNORE,\
                CONSTRAINT [Connector_pin_role]\
                    FOREIGN KEY([Connector_pin_role])\
                    REFERENCES [CONNECTOR_PIN_ROLE] ( [rowid] ),\
                CONSTRAINT [Connection_name]\
                    FOREIGN KEY([Connection_name])\
                    REFERENCES [CONNECTION_NAME] ( [rowid] ),\
                CONSTRAINT [Line_type]\
                    FOREIGN KEY([Line_type])\
                    REFERENCES [LINE_TYPE] ( [rowid] ),\
                CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [rowid] ),\
                CONSTRAINT [Connector]\
                    FOREIGN KEY([Connector])\
                    REFERENCES [CONNECTOR] ( [rowid] ));";
     database_manager->create_table(create_table_query);
}
