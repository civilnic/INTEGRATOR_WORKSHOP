#ifndef MICD_UNIT_H
#define MICD_UNIT_H

#include "micd_element.h"

class micd_unit : public micd_element
{
public:
    micd_unit(sql_database_manager *database_manager);
};

#endif // MICD_UNIT_H
