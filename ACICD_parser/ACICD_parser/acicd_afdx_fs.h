#ifndef ACICD_AFDX_FS_H
#define ACICD_AFDX_FS_H

#include <string>
#include <QString>
#include <map>
#include "acicd_element.h"

class acicd_afdx_FS : public acicd_element
{
public:
    acicd_afdx_FS(sql_database_manager *database_manager);
};

#endif // ACICD_AFDX_FS_H
