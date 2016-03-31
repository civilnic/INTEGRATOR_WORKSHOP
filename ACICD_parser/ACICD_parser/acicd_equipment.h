#ifndef ACICD_EQUIPMENT_H
#define ACICD_EQUIPMENT_H

#include <string>
#include <QString>
#include <map>


class acicd_equipment
{
public:
    acicd_equipment();
    bool set_parameters(int field,std::string value);
    std::map<int,std::string> DB_FIELDS_EQUIPMENT;
private:
    int id;
    std::map<int,QString> DB_FIELDS_VALUES;
};




#endif // ACICD_EQUIPMENT_H
