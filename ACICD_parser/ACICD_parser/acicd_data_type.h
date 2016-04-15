#ifndef ACICD_DATA_TYPE_H
#define ACICD_DATA_TYPE_H


#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"


class acicd_data_type : public acicd_element
{
public:
    acicd_data_type(sql_database_manager *database_manager);
};

#endif // ACICD_DATA_TYPE_H
