#ifndef ACICD_EQUIPMENT_H
#define ACICD_EQUIPMENT_H

#include <string>
#include <QString>
#include <map>


class acicd_equipment
{
public:
    acicd_equipment();
private:
    std::string table_name="EQUIPMENT";
};


const QString DB_QUERY_CREATE_EQUIPMENT="\
    CREATE TABLE IF NOT EXISTS [EQUIPMENT](      \
     [id] INTEGER CONSTRAINT [pk_EQUIPMENT] PRIMARY KEY  NOT NULL,  \
     [Name] VARCHAR( 45 ) NULL,                                     \
     [Description] VARCHAR( 45 ) NULL,  \
     [Type] VARCHAR( 45 ) NULL,\
     [EMC Protection] VARCHAR( 45 ) NULL,\
     [Zone] VARCHAR( 45 ) NULL\
    );\
";




#endif // ACICD_EQUIPMENT_H
