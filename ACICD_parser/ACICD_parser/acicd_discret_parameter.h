#ifndef ACICD_DISCRET_PARAMETER_H
#define ACICD_DISCRET_PARAMETER_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_discret_parameter : public acicd_element
{
public:
    acicd_discret_parameter(sql_database_manager *database_manager);
};

#endif // ACICD_DISCRET_PARAMETER_H
