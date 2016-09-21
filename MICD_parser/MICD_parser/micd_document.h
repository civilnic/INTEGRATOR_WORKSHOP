#ifndef MICD_DOCUMENT_H
#define MICD_DOCUMENT_H


#include <iostream>
#include <xls.h>
#include <boost/algorithm/string.hpp>

#include "sql_database_manager.h"

#include "micd_header.h"

#include "micd_com_format.h"
#include "micd_com_mode.h"
#include "micd_data_type.h"
#include "micd_interface_level.h"
#include "micd_port_in.h"
#include "micd_port_out.h"
#include "micd_unit.h"


using namespace std;
using namespace xls;

class micd_document
{
public:
    micd_document(sql_database_manager *database_manager, const char * filename);
};

#endif // MICD_DOCUMENT_H
