#ifndef ACICD_DISCRET_LINE_H
#define ACICD_DISCRET_LINE_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_discret_line : public acicd_element
{
public:
    acicd_discret_line(sql_database_manager *database_manager);
};

#endif // ACICD_DISCRET_LINE_H
