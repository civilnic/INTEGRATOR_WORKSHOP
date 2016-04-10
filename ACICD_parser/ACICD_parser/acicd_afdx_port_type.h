#ifndef ACICD_AFDX_PORT_TYPE_H
#define ACICD_AFDX_PORT_TYPE_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_afdx_port_type : public acicd_element
{
public:
    acicd_afdx_port_type(sql_database_manager *database_manager);
};

#endif // ACICD_AFDX_PORT_TYPE_H
