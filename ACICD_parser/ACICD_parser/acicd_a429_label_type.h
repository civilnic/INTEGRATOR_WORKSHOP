#ifndef ACICD_A429_LABEL_TYPE_H
#define ACICD_A429_LABEL_TYPE_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_a429_label_type : public acicd_element
{
public:
    acicd_a429_label_type(sql_database_manager *database_manager);
};

#endif // ACICD_A429_LABEL_TYPE_H
