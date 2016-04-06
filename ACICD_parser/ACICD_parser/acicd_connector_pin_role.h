#ifndef ACICD_CONNECTOR_PIN_ROLE_H
#define ACICD_CONNECTOR_PIN_ROLE_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_connector_pin_role : public acicd_element
{
public:
    acicd_connector_pin_role(sql_database_manager *database_manager);
};

#endif // ACICD_CONNECTOR_PIN_ROLE_H
