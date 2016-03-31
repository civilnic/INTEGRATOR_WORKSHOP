#include "acicd_equipment.h"

acicd_equipment::acicd_equipment()
{
    DB_FIELDS_EQUIPMENT = { { 2, "Name" },
                          { 3, "Description" },
                          { 4, "Type" },
                          { 5, "EMC Protection" },
                          { 6, "Zone" }
                        };
}

bool acicd_equipment::set_parameters(int field,std::string value)
{
    DB_FIELDS_VALUES[field]=QString::fromStdString(value);
    return true;
}
