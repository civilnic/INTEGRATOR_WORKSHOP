#ifndef ACICD_CONNECTION_NAME_H
#define ACICD_CONNECTION_NAME_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_connection_name : public acicd_element
{
public:
    acicd_connection_name(sql_database_manager *database_manager);
};

#endif // ACICD_CONNECTION_NAME_H
