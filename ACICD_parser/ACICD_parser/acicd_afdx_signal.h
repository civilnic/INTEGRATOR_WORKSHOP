#ifndef ACICD_AFDX_SIGNAL_H
#define ACICD_AFDX_SIGNAL_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_afdx_signal : public acicd_element
{
public:
    acicd_afdx_signal(sql_database_manager *database_manager);
};

#endif // ACICD_AFDX_SIGNAL_H
