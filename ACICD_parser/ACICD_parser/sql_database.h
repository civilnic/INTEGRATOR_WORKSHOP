#ifndef SQL_DATABASE_H
#define SQL_DATABASE_H

#include <QSqlDatabase>
#include <QtSql>

class sql_database
{
public:
    sql_database(void);
    QSqlDatabase create_database(void);
    void open_database(QSqlDatabase db);
    void set_dbname(std::string name);
    std::string get_dbname(void);
    QSqlDatabase get_db(void);
private:
    QSqlDatabase database;
    QString driver_type="QSQLITE";
    QString db_name="INTEGRATOR_WORKSHOP.db";
    QString db_user="root";
    QString db_pass="";
    QString db_hostname="localhost";
};

#endif // SQL_DATABASE_H
