#include "mysql_database.h"

mysql_database::mysql_database(void)
{

}

QSqlDatabase mysql_database::set_database(std::string name)
{
    db_name=QString::fromStdString(name);

    database = QSqlDatabase::addDatabase(driver_type,db_cnx_name);
    database.setDatabaseName(db_name);
    database.setUserName(this->db_user);
    database.setPassword(this->db_pass);
    database.setHostName(this->db_hostname);
    return database;
}

void mysql_database::set_dbname(std::string name)
{
    db_name=QString::fromStdString(name);
}

std::string mysql_database::get_dbname(void)
{
    return db_name.toStdString();
}
