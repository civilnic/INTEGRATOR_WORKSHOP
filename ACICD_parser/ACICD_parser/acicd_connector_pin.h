#ifndef ACICD_CONNECTOR_PIN_H
#define ACICD_CONNECTOR_PIN_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_connector_pin : public acicd_element
{
public:
    acicd_connector_pin(sql_database_manager *database_manager);
};

#endif // ACICD_CONNECTOR_PIN_H
