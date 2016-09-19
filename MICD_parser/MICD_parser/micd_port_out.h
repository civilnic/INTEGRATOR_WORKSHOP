#ifndef MICD_PORT_OUT_H
#define MICD_PORT_OUT_H

#include "micd_element.h"

class micd_port_out : public micd_element
{
public:
    micd_port_out(sql_database_manager *database_manager);
};

#endif // MICD_PORT_OUT_H
