#ifndef SQL_DATABASE_H
#define SQL_DATABASE_H

#include <iostream>
#include <QSqlDatabase>
#include <QtSql>

class sql_database_manager
{
public:
    sql_database_manager(void);
    QSqlDatabase create_database(void);
    void open_database(void);
    void set_dbname(std::string name);

    bool create_table(QString TABLE_CREATION_QUERY);

    std::string get_dbname(void);
    QSqlDatabase *get_db(void);

private:
    QSqlDatabase database;
    QString driver_type="QSQLITE";
    QString db_name="INTEGRATOR_WORKSHOP.db";
    QString db_user="root";
    QString db_pass="";
    QString db_hostname="localhost";



};
#endif // SQL_DATABASE_H
