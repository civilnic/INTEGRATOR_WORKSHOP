#include "micd_unit.h"

micd_unit::micd_unit(sql_database_manager *database_manager) : micd_simple_tab (database_manager)
{
    DB_FIELDS= { { 2, "Name" }
               };

    DB_table_name="UNITS";


    this->init_table(database_manager);

}
