#include "acicd_element.h"

acicd_element::acicd_element(sql_database_manager *database_manager) : sql_element (database_manager)
{
    update_query.clear();

    id=-1;

    sql_element_field=":ACICD";

    BDD=database_manager;
    db=(*BDD).get_db();
}
