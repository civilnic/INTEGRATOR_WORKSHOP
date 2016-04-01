#ifndef ACICD_EQUIPMENT_H
#define ACICD_EQUIPMENT_H

#include <string>
#include <QString>
#include <map>

template<typename T>
struct FIELDS_VALUES {
    T indice {};
    QString field_name {};
    QString value {};
};


class acicd_equipment
{
public:
    acicd_equipment();
    bool set_parameters(int field,std::string value);
    QString get_name(void);
    QString insert_query;

    std::map<int,std::string> DB_FIELDS_EQUIPMENT;
    std::map<QString,QString> DB_FIELDS_VALUES;
private:
    int id;


};




#endif // ACICD_EQUIPMENT_H
