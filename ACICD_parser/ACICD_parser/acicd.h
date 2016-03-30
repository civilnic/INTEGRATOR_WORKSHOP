#ifndef ACICD_H
#define ACICD_H

#include <string>
#include <fstream>
#include <iostream>

#include <QSqlDatabase>
#include <QtSql>
#include <regex>

#include "acicd_header.h"
#include "acicd_equipment.h"
#include "acicd_connector.h"
#include "sql_database_manager.h"

class ACICD
{
public:
    ACICD(sql_database_manager *BDD,QString path_name);
    bool parse_ACICD(void);
private:
    int db_id;
    QString path_name;
    QSqlDatabase *db;
};






#endif // ACICD_H
