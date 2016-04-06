#include "acicd_connector_pin_role.h"

acicd_connector_pin_role::acicd_connector_pin_role(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    id=-1;
    BDD=database_manager;
    db=(*BDD).get_db();

    DB_FIELDS= { { 2, "Name" },
               };

    DB_table_name="CONNECTOR_PIN_ROLE";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(NULL,:Name)").arg(DB_table_name);
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query=QString("\
       CREATE TABLE IF NOT EXISTS [%1](\
        [id] INTEGER CONSTRAINT [pk_Connector_Pin_Role] NOT NULL PRIMARY KEY AUTOINCREMENT,\
        [Name] VARCHAR( 45 ) NULL\
       );\n\
       ").arg(DB_table_name);
}
