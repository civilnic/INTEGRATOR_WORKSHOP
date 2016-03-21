#include <iostream>
#include <string>
#include <fstream>


#include "sql_database.h"
#include <QtSql>

#include "boost/lexical_cast.hpp"
#include <regex>

#include "acicd.h"

#define q2c(string) string.toStdString()

using namespace std;


void Query2DB(QSqlDatabase db,std::string &fields,std::string &values)
{
    QSqlQuery query(db);

    //    finalize query string
    fields+=") ";
    values+=")";

    fields = std::regex_replace(fields, std::regex("\\(, "), "\(");
    values = std::regex_replace(values, std::regex("\\(, "), "\(");

    //    concatenate fields and values into one QString for execution
    QString QueryforQT;
    QueryforQT=QString::fromStdString(fields+values);

    //    concatenate fields and values into one QString for execution
    query.prepare(QueryforQT);

    if( !query.exec() )
    {
        std::cout <<"query error:  " +   QueryforQT.toStdString()   << std::endl;
        qDebug() << query.lastError();
    }
    else
    {
//        qDebug() << "query executed succesfully !";
    }
}





int main(int argc, char** argv)
{


    sql_database BDD;
    QSqlDatabase db=BDD.create_database();
    BDD.open_database(db);

    db.close();
    return 0;
}



