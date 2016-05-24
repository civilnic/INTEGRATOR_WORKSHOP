#ifndef ACICD_UNIT_H
#define ACICD_UNIT_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_unit : public acicd_element
{
public:
    acicd_unit(sql_database_manager *database_manager);
};

#endif // ACICD_UNIT_H
