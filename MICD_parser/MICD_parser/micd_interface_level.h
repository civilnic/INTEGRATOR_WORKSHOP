#ifndef MICD_INTERFACE_LEVEL_H
#define MICD_INTERFACE_LEVEL_H


#include "micd_element.h"

class micd_interface_level : public micd_element
{
public:
    micd_interface_level(sql_database_manager *database_manager);
};

#endif // MICD_INTERFACE_LEVEL_H
