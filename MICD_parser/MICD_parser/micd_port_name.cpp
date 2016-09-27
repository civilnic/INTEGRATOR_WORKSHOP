#include "micd_port_name.h"

micd_port_name::micd_port_name(sql_database_manager *database_manager) : micd_simple_tab (database_manager)
{
    DB_FIELDS= { { 0, "Name" }
               };

    DB_table_name="PORTS_NAME";

    this->init_table(database_manager);

}
