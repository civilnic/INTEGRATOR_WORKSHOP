#ifndef ACICD_ANA_PARAMETER_H
#define ACICD_ANA_PARAMETER_H


#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_ANA_parameter : public acicd_element
{
public:
    acicd_ANA_parameter(sql_database_manager *database_manager);
};

#endif // ACICD_ANA_PARAMETER_H
