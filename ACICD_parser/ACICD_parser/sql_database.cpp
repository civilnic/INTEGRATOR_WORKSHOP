#include "sql_database.h"

sql_database::sql_database(void)
{

}

QSqlDatabase sql_database::create_database()
{
    database = QSqlDatabase::addDatabase(driver_type);
    database.setDatabaseName(db_name);
    database.setUserName(this->db_user);
    database.setPassword(this->db_pass);
    database.setHostName(this->db_hostname);
    return database;
}

void sql_database::open_database(QSqlDatabase db)
{
    if( !db.open() )
    {
      qDebug() << db.lastError();
      qFatal( "Failed to connect." );
    }else{
      qDebug( "Connected!" );
    }
    db.transaction();
}

void sql_database::set_dbname(std::string name)
{
    db_name=QString::fromStdString(name);
}

std::string sql_database::get_dbname(void)
{
    return db_name.toStdString();
}
