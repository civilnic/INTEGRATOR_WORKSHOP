#ifndef ACICD_ELEMENT_H
#define ACICD_ELEMENT_H

#include <string>
#include <QString>
#include <map>
#include <boost/unordered_map.hpp>

#include "sql_element.h"

class acicd_element : public sql_element
{
public:
    acicd_element(sql_database_manager *database_manager);

};

#endif // ACICD_ELEMENT_H
