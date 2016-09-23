#ifndef SQL_ELEMENT_H
#define SQL_ELEMENT_H

#include <string>
#include <QString>
#include <map>
#include <boost/unordered_map.hpp>

#include "sql_database_manager.h"

class sql_element
{
public:
    sql_element(sql_database_manager *database_manager);
    bool set_parameters(int field,std::string value);
    bool modify_parameters(std::map<int,std::string> DB_NEW_FIELDS);
    bool create_table(void);
    bool insert_intable_new(int ref_sql_element);

    QString get_value(QString field);
    void create_update_query(QString field);
    void set_reference(QString field,int ref_id);
    void update_value(QString field,QString value);
    void set_value(QString field,QString value);
    int get_id(void);

    std::map<int,std::string> DB_FIELDS;
    std::map<QString,QString> DB_VALUES;
    QString create_table_query;

protected :
    int id;

    int is_element_exist_new(int ref_sql_element);
    QString sql_element_field;

    QSqlDatabase *db;
    sql_database_manager *BDD;

    QString test_field;
    QString test_query;

    QString insert_query;
    QString update_query;


    QString DB_table_name;

    boost::unordered_map<std::string,int> Element_collection;

};

#endif // SQL_ELEMENT_H
