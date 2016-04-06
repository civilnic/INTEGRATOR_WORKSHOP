#ifndef ACICD_CONNECTOR_H
#define ACICD_CONNECTOR_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_connector : public acicd_element
{
public:
    acicd_connector(sql_database_manager *database_manager);
};



#endif // ACICD_CONNECTOR_H
