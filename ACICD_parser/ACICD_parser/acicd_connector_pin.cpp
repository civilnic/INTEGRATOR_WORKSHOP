#include "acicd_connector_pin.h"

acicd_connector_pin::acicd_connector_pin(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    id=-1;
    BDD=database_manager;
    db=(*BDD).get_db();

    DB_FIELDS= { { 4, "Connector_pin" }
               };

    DB_table_name="CONNECTOR_PIN";
    test_field="Connector_pin";

    insert_query=QString("INSERT INTO %1 VALUES(NULL,:Connector_pin,:Connector_pin_role,:Connection_name,:Line_type,:Connector,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query="CREATE TABLE IF NOT EXISTS [CONNECTOR_PIN](\
            [id] INTEGER CONSTRAINT [pk_CONNECTOR_PIN] NOT NULL PRIMARY KEY AUTOINCREMENT,\
            [Connector_pin] VARCHAR( 45 ) NULL,\
            [Connector_pin_role] INTEGER NULL,\
            [Connection_name] INTEGER NULL,\
            [Line_type] INTEGER NULL,\
            [Connector] INTEGER NULL,\
            [ACICD] INTEGER NULL,\
                CONSTRAINT [Connector_pin_role]\
                    FOREIGN KEY([Connector_pin_role])\
                    REFERENCES [CONNECTOR_PIN_ROLE] ( [id] ),\
                CONSTRAINT [Connection_name]\
                    FOREIGN KEY([Connection_name])\
                    REFERENCES [CONNECTION_NAME] ( [id] ),\
                CONSTRAINT [Line_type]\
                    FOREIGN KEY([Line_type])\
                    REFERENCES [LINE_TYPE] ( [id] ),\
                CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [id] ),\
                CONSTRAINT [Connector]\
                    FOREIGN KEY([Connector])\
                    REFERENCES [CONNECTOR] ( [id] ));";


     database_manager->create_table(create_table_query);
}
