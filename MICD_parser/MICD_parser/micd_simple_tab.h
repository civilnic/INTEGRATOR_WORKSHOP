#ifndef MICD_SIMPLE_TAB_H
#define MICD_SIMPLE_TAB_H

#include "micd_element.h"

class micd_simple_tab : public micd_element
{
public:
    micd_simple_tab(sql_database_manager *database_manager);
    init_table(sql_database_manager *database_manager);

};

#endif // MICD_SIMPLE_TAB_H
