#ifndef MICD_PORT_IN_H
#define MICD_PORT_IN_H

#include "micd_element.h"

class micd_port_in : public micd_element
{
public:
    micd_port_in(sql_database_manager *database_manager);
};

#endif // MICD_PORT_IN_H
