#ifndef ACICD_EQUIPMENT_H
#define ACICD_EQUIPMENT_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_equipment : public acicd_element
{
public:
    acicd_equipment(sql_database_manager *database_manager);

};

#endif // ACICD_EQUIPMENT_H
