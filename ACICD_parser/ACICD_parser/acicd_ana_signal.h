#ifndef ACICD_ANA_SIGNAL_H
#define ACICD_ANA_SIGNAL_H


#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_ANA_signal : public acicd_element
{
public:
    acicd_ANA_signal(sql_database_manager *database_manager);
};

#endif // ACICD_ANA_SIGNAL_H
