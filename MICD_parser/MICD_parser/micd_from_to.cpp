#include "micd_from_to.h"

micd_from_to::micd_from_to(sql_database_manager *database_manager) : micd_simple_tab (database_manager)
{
    DB_FIELDS= { { 9, "Name" }
               };

    DB_table_name="FROM_TO";

    this->init_table(database_manager);

}
