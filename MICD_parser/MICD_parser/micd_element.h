#ifndef MICD_ELEMENT_H
#define MICD_ELEMENT_H

#include <string>
#include <QString>
#include <map>
#include <boost/unordered_map.hpp>

#include "sql_element.h"

class micd_element : public sql_element
{
public:
    micd_element(sql_database_manager *database_manager);

};

#endif // MICD_ELEMENT_H
