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


class ACICD
{
public:
    ACICD(QSqlDatabase *db,std::string path_name);
    bool parse_ACICD(void);
private:
    int db_id;
    std::string path_name;
    QSqlDatabase *db;
    bool create_ACICD_tables(void);
};


const QString DB_QUERY_CREATE_ACICD="\
CREATE TABLE IF NOT EXISTS [ACICD](\
 [id] INTEGER CONSTRAINT [pk_ACICD] PRIMARY KEY  NOT NULL,\
 [Name] VARCHAR( 45 ) NULL,\
 [Path] VARCHAR( 45 ) NULL,\
 [Micd] INTEGER NULL,\
 [Equipment] INTEGER NULL,\
 [Version] VARCHAR( 45 ) NULL,\
  CONSTRAINT [Equipment]\
  FOREIGN KEY([Equipment])\
    REFERENCES [EQUIPMENT] ( [id] ));\n";




#endif // ACICD_H
