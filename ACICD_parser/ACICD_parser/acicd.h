#ifndef ACICD_H
#define ACICD_H

#include <string>
#include <fstream>
#include <iostream>

#include "csv_parser.h"
#include "csv_stl_traits.h"
#include "csv_data.h"
#include <boost/optional/optional_io.hpp>
#include "boost/lexical_cast.hpp"

#include "acicd_header.h"
#include "acicd_equipment.h"
#include "acicd_connector.h"

#include <QSqlDatabase>
#include <QtSql>
#include <regex>

class ACICD
{
public:
    ACICD(QSqlDatabase db,std::string path_name);
    bool parse_ACICD(void);
    bool create_ACICD_tables(void);
    bool ACICD2DB(void);

private:
    int db_id;
    std::string path_name;
    QSqlDatabase db;
    dvp::csv_parser<dvp::csv_stl_traits> parser;
    dvp::csv_data data;
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
    REFERENCES [EQUIPMENT] ( [id] )\
);\n\
";


#endif // ACICD_H
