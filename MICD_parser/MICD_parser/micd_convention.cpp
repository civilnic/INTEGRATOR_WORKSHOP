#include "micd_convention.h"

micd_convention::micd_convention(sql_database_manager *database_manager) : micd_simple_tab (database_manager)
{
    DB_FIELDS= { { 4, "Name" }
               };

    DB_table_name="CONVENTION";


    this->init_table(database_manager);
}
