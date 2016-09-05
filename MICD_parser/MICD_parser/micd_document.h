#ifndef MICD_DOCUMENT_H
#define MICD_DOCUMENT_H


#include <iostream>
#include <xls.h>
#include <boost/algorithm/string.hpp>

#include "sql_database_manager.h"

using namespace std;
using namespace xls;

class micd_document
{
public:
    micd_document(sql_database_manager *database_manager, const char * filename);
};

#endif // MICD_DOCUMENT_H
