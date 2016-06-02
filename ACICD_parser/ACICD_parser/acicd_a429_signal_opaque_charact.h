#ifndef ACICD_A429_SIGNAL_OPAQUE_CHARACT_H
#define ACICD_A429_SIGNAL_OPAQUE_CHARACT_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_a429_signal_opaque_charact : public acicd_element
{
public:
    acicd_a429_signal_opaque_charact(sql_database_manager *database_manager);
};

#endif // ACICD_A429_SIGNAL_OPAQUE_CHARACT_H
