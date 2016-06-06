#ifndef ACICD_ANA_LINE_H
#define ACICD_ANA_LINE_H


#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"


class acicd_ANA_line : public acicd_element
{
public:
    acicd_ANA_line(sql_database_manager *database_manager);
};

#endif // ACICD_ANA_LINE_H
