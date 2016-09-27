#include "micd_enum.h"

micd_enum::micd_enum(sql_database_manager *database_manager) : micd_simple_tab (database_manager)
{
    DB_FIELDS= { { 13, "Name" }
               };

    DB_table_name="ENUM";

    this->init_table(database_manager);

}
