#ifndef MICD_COM_MODE_H
#define MICD_COM_MODE_H


#include "micd_simple_tab.h"

class micd_com_mode : public micd_simple_tab
{
public:
    micd_com_mode(sql_database_manager *database_manager);
};

#endif // MICD_COM_MODE_H
