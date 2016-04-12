#ifndef ACICD_AFDX_NETWORK_H
#define ACICD_AFDX_NETWORK_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_afdx_network : public acicd_element
{
public:
    acicd_afdx_network(sql_database_manager *database_manager);
};

#endif // ACICD_AFDX_NETWORK_H
