#ifndef ACICD_MESSAGE_H
#define ACICD_MESSAGE_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_afdx_message : public acicd_element
{
public:
    acicd_afdx_message(sql_database_manager *database_manager);
};

#endif // ACICD_MESSAGE_H
