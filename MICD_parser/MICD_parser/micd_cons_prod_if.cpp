#include "micd_cons_prod_if.h"

micd_cons_prod_if::micd_cons_prod_if(sql_database_manager *database_manager) : micd_simple_tab (database_manager)
{
    DB_FIELDS= { { 14, "Name" }
               };

    DB_table_name="CONS_PROD_IF";


    this->init_table(database_manager);
}

