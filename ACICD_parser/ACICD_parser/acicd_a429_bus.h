#ifndef ACICD_A429_BUS_H
#define ACICD_A429_BUS_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_a429_bus : public acicd_element
{
public:
    acicd_a429_bus(sql_database_manager *database_manager);
};

#endif // ACICD_A429_BUS_H
