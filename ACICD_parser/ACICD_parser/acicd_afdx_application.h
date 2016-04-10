#ifndef ACICD_AFDX_APPLICATION_H
#define ACICD_AFDX_APPLICATION_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_afdx_application : public acicd_element
{
public:
    acicd_afdx_application(sql_database_manager *database_manager);
};

#endif // ACICD_AFDX_APPLICATION_H
