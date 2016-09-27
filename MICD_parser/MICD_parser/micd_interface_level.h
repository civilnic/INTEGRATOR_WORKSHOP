#ifndef MICD_INTERFACE_LEVEL_H
#define MICD_INTERFACE_LEVEL_H


#include "micd_simple_tab.h"

class micd_interface_level : public micd_simple_tab
{
public:
    micd_interface_level(sql_database_manager *database_manager);
};

#endif // MICD_INTERFACE_LEVEL_H
