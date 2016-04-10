#ifndef ACICD_AFDX_RX_PORT_H
#define ACICD_AFDX_RX_PORT_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_afdx_rx_port : public acicd_element
{
public:
    acicd_afdx_rx_port(sql_database_manager *database_manager);
};

#endif // ACICD_AFDX_RX_PORT_H
