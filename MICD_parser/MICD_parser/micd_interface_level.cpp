#include "micd_interface_level.h"

micd_interface_level::micd_interface_level(sql_database_manager *database_manager) : micd_simple_tab (database_manager)
{
    DB_FIELDS= { { 16, "Name" }
               };

    DB_table_name="INTERFACE_LEVEL";

    this->init_table(database_manager);

}

