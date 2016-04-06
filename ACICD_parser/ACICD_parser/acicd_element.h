#ifndef ACICD_ELEMENT_H
#define ACICD_ELEMENT_H

#include <string>
#include <QString>
#include <map>
#include "sql_database_manager.h"

class acicd_element
{
public:
    acicd_element(sql_database_manager *database_manager);
    bool set_parameters(int field,std::string value);
    bool create_table(void);
    int insert_intable(void);
    int is_element_exist(QString Name);
    QString get_name(void);
    int get_id(void);

    std::map<int,std::string> DB_FIELDS;
    std::map<QString,QString> DB_VALUES;
    QString create_table_query;
protected :
    int id;
    QSqlDatabase *db;
    sql_database_manager *BDD;
    QString insert_query;
    QString test_query;
    QString DB_table_name;
    QString test_field;
};

#endif // ACICD_ELEMENT_H
