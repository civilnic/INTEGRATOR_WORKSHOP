#ifndef ACICD_AFDX_FDS_H
#define ACICD_AFDX_FDS_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_afdx_FDS : public acicd_element
{
public:
    acicd_afdx_FDS(sql_database_manager *database_manager);
};

#endif // ACICD_AFDX_FDS_H
