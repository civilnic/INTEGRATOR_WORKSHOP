#include "micd_description.h"

micd_description::micd_description(sql_database_manager *database_manager) : micd_simple_tab (database_manager)
{
    DB_FIELDS= { { 3, "Name" }
               };

    DB_table_name="DESCRIPTIONS";


    this->init_table(database_manager);
}
