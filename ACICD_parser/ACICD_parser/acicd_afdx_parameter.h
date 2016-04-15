#ifndef ACICD_AFDX_PARAMETER_H
#define ACICD_AFDX_PARAMETER_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_afdx_parameter : public acicd_element
{
public:
    acicd_afdx_parameter(sql_database_manager *database_manager);
};

#endif // ACICD_AFDX_PARAMETER_H
