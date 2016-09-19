#include "micd_element.h"

micd_element::micd_element(sql_database_manager *database_manager) : sql_element (database_manager)
{
    update_query.clear();

    id=-1;
    ref_sql_element=-1;
    sql_element_field=":MICD";

    BDD=database_manager;
    db=(*BDD).get_db();
}


