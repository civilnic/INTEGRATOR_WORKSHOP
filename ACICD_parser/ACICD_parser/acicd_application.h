#ifndef ACICD_APPLICATION_H
#define ACICD_APPLICATION_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_application : public acicd_element
{
public:
    acicd_application(sql_database_manager *database_manager);
};

#endif // ACICD_APPLICATION_H
