#ifndef MICD_UNIT_H
#define MICD_UNIT_H

#include "micd_simple_tab.h"

class micd_unit : public micd_simple_tab
{
public:
    micd_unit(sql_database_manager *database_manager);
};

#endif // MICD_UNIT_H
