#ifndef MICD_DESCRIPTION_H
#define MICD_DESCRIPTION_H

#include "micd_simple_tab.h"

class micd_description : public micd_simple_tab
{
public:
    micd_description(sql_database_manager *database_manager);
};

#endif // MICD_DESCRIPTION_H
