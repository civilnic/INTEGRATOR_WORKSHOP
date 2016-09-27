#include "micd_data_type.h"

micd_data_type::micd_data_type(sql_database_manager *database_manager) : micd_simple_tab (database_manager)
{
    DB_FIELDS= { { 1, "Name" }
               };

    DB_table_name="DATA_TYPE";

    this->init_table(database_manager);

}
