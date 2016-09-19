#ifndef MICD_DATA_TYPE_H
#define MICD_DATA_TYPE_H

#include "micd_element.h"

class micd_data_type : public micd_element
{
public:
    micd_data_type(sql_database_manager *database_manager);
};

#endif // MICD_DATA_TYPE_H
