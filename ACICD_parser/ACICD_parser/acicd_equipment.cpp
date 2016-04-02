#include "acicd_equipment.h"

acicd_equipment::acicd_equipment()
{
    DB_FIELDS_EQUIPMENT = { { 2, "Name" },
                          { 3, "Description" },
                          { 4, "Type" },
                          { 5, "EMC_Protection" },
                          { 6, "Zone" },
                          { 7, "FIN" }
                        };
}

bool acicd_equipment::set_parameters(int field,std::string value)
{

    DB_FIELDS_VALUES[QString::fromStdString(DB_FIELDS_EQUIPMENT[field])]=QString::fromStdString(value);
    return true;
}

QString acicd_equipment::get_name(void)
{
    return DB_FIELDS_VALUES["Name"];
}
