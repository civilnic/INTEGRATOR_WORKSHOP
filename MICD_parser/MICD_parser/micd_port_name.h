#ifndef MICD_PORT_NAME_H
#define MICD_PORT_NAME_H

#include "micd_element.h"

class micd_port_name : public micd_element
{
public:
    micd_port_name(sql_database_manager *database_manager);
};

#endif // MICD_PORT_NAME_H
