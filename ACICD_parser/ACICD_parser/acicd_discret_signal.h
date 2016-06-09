#ifndef ACICD_DISCRET_SIGNAL_H
#define ACICD_DISCRET_SIGNAL_H


#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_discret_signal : public acicd_element
{
public:
    acicd_discret_signal(sql_database_manager *database_manager);
};

#endif // ACICD_DISCRET_SIGNAL_H
