#ifndef ACICD_ELEMENT_H
#define ACICD_ELEMENT_H

#include <string>
#include <QString>
#include <map>
#include <boost/unordered_map.hpp>

#include "sql_database_manager.h"

class acicd_element
{
public:
    acicd_element(sql_database_manager *database_manager);
    bool set_parameters(int field,std::string value);
    bool modify_parameters(std::map<int,std::string> DB_NEW_FIELDS);
    bool create_table(void);
    bool insert_intable(void);
    bool insert_intable_new(int acicd_reference);
    int is_element_exist(QString Name);
    int is_element_exist_new(void);
    QString get_value(QString field);
    void create_update_query(QString field);
    void set_reference(QString field,int ref_id);
    void set_value(QString field,QString value);
    int get_id(void);

    std::map<int,std::string> DB_FIELDS;
    std::map<QString,QString> DB_VALUES;
    QString create_table_query;
protected :
    int id;
    int ref_acicd;
    QSqlDatabase *db;
    sql_database_manager *BDD;
    QString insert_query;
    QString test_query;
    QString update_query;
    QString DB_table_name;
    QString test_field;
    boost::unordered_map<std::string,int> Element_collection;

};

#endif // ACICD_ELEMENT_H
