#ifndef ACICD_AFDX_PORT_CHARACTERISTIC_H
#define ACICD_AFDX_PORT_CHARACTERISTIC_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_afdx_port_characteristic : public acicd_element
{
public:
    acicd_afdx_port_characteristic(sql_database_manager *database_manager);
};

#endif // ACICD_AFDX_PORT_CHARACTERISTIC_H
