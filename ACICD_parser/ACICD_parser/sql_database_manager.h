#ifndef SQL_DATABASE_H
#define SQL_DATABASE_H

#include <iostream>
#include <fstream>
#include <QSqlDatabase>
#include <QtSql>
#include <QFile>



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
    QTextStream sql_log_file;

private:
    QSqlDatabase database;
    QString driver_type="QSQLITE";
    QString db_name="INTEGRATOR_WORKSHOP.db";
    QString db_user="root";
    QString db_pass="";
    QString db_hostname="localhost";
    QFile log_file;



};
#endif // SQL_DATABASE_H
