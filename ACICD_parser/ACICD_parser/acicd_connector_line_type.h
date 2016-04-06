#ifndef ACICD_CONNECTOR_LINE_TYPE_H
#define ACICD_CONNECTOR_LINE_TYPE_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_connector_line_type : public acicd_element
{
public:
    acicd_connector_line_type(sql_database_manager *database_manager);
};

#endif // ACICD_CONNECTOR_LINE_TYPE_H
