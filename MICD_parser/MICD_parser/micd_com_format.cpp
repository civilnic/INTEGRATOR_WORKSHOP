#include "micd_com_format.h"

micd_com_format::micd_com_format(sql_database_manager *database_manager) : micd_simple_tab (database_manager)
{
    DB_FIELDS= { { 7, "Name" }
               };

    DB_table_name="COM_FORMAT";


    this->init_table(database_manager);
}
