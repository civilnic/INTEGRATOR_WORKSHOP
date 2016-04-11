#ifndef ACICD_AFDX_MESSAGE_TYPE_H
#define ACICD_AFDX_MESSAGE_TYPE_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_afdx_message_type : public acicd_element
{
public:
    acicd_afdx_message_type(sql_database_manager *database_manager);
};

#endif // ACICD_AFDX_MESSAGE_TYPE_H