#include "micd_com_mode.h"

micd_com_mode::micd_com_mode(sql_database_manager *database_manager) : micd_simple_tab (database_manager)
{
    DB_FIELDS= { { 8, "Name" }
               };

    DB_table_name="COM_MODE";


    this->init_table(database_manager);
}
