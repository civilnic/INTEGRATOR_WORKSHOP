#ifndef MYSQL_DATABASE_H
#define MYSQL_DATABASE_H

#include <QSqlDatabase>
#include <QtSql>

class mysql_database
{
public:
    mysql_database();
    ~mysql_database();
    QSqlDatabase mysql_database(std::string db_name);
    void set_dbname(std::string db_name);
    std::string get_dbname(void);
private:
    QSqlDatabase database;
    std::string driver_type="QMYSQL";
    std::string db_name="mydb";
    std::string db_user="everybody";
    std::string db_pass="";
};

mysql_database::mysql_database()
{

}

QSqlDatabase mysql_database::mysql_database(std::string db_name)
{
    this->db_name=db_name;

    QSqlDatabase db = QSqlDatabase::addDatabase(this->driver_type);
    db.setDatabaseName(db_name);
    db.setUserName(this->db_user);
    db.setPassword(this->db_pass);

    return db;
}

void mysql_database::set_dbname(std::string db_name)
{
    this->db_name=db_name;
}

std::string mysql_database::get_dbname(void)
{
    return this->db_name;
}


#endif // MYSQL_DATABASE_H
