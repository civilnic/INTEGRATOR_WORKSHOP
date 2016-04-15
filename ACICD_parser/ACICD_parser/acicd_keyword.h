#ifndef ACICD_KEYWORD_H
#define ACICD_KEYWORD_H


#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_keyword : public acicd_element
{
public:
    acicd_keyword(sql_database_manager *database_manager);
};

#endif // ACICD_KEYWORD_H
