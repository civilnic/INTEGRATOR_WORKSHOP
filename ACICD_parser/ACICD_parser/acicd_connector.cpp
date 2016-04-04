#include "acicd_connector.h"

acicd_connector::acicd_connector(sql_database_manager *database_manager)
{
    id=-1;
    BDD=database_manager;
    db=(*BDD).get_db();
}

bool acicd_connector::set_parameters(int field,std::string value)
{

    DB_VALUES_EQUIPMENT[QString::fromStdString(DB_FIELDS_EQUIPMENT[field])]=QString::fromStdString(value);
    return true;
}

QString acicd_connector::get_name(void)
{
    return DB_VALUES_EQUIPMENT["Name"];
}

int acicd_connector::get_id(void)
{
    return id;
}
