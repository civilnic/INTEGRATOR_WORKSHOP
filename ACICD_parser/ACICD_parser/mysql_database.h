#ifndef MYSQL_DATABASE_H
#define MYSQL_DATABASE_H

#include <QSqlDatabase>
#include <QtSql>

class mysql_database
{
public:
    mysql_database(void);
    QSqlDatabase set_database(std::string name);
    void set_dbname(std::string name);
    std::string get_dbname(void);
    QSqlDatabase get_db(void);
private:
    QSqlDatabase database;
    QString driver_type="QMYSQL";
    QString db_name="mydb";
    QString db_cnx_name="myconnection";
    QString db_user="everybody";
    QString db_pass="";
};

#endif // MYSQL_DATABASE_H
