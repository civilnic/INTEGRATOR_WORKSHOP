#ifndef MICD_CONS_PROD_IF_H
#define MICD_CONS_PROD_IF_H

#include "micd_simple_tab.h"

class micd_cons_prod_if : public micd_simple_tab
{
public:
    micd_cons_prod_if(sql_database_manager *database_manager);
};

#endif // MICD_CONS_PROD_IF_H
