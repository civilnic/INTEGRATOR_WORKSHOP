#ifndef ACICD_VL_H
#define ACICD_VL_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_VL : public acicd_element
{
public:
    acicd_VL(sql_database_manager *database_manager);
};

#endif // ACICD_VL_H
