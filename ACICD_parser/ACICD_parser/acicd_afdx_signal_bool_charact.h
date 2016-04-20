#ifndef ACICD_AFDX_SIGNAL_BOOL_CHARACT_H
#define ACICD_AFDX_SIGNAL_BOOL_CHARACT_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_afdx_signal_bool_charact : public acicd_element
{
public:
    acicd_afdx_signal_bool_charact(sql_database_manager *database_manager);
    bool insert_intable(void);
};

#endif // ACICD_AFDX_SIGNAL_BOOL_CHARACT_H
