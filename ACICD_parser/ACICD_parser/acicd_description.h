#ifndef ACICD_DESCRIPTION_H
#define ACICD_DESCRIPTION_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_description : public acicd_element
{
public:
    acicd_description(sql_database_manager *database_manager);
};

#endif // ACICD_DESCRIPTION_H
