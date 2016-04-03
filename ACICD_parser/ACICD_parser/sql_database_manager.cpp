#include "sql_database_manager.h"

sql_database_manager::sql_database_manager(void)
{
    printf("creation objet sql_database\n");
    this->create_database();
    this->open_database();
}

QSqlDatabase sql_database_manager::create_database()
{
    database = QSqlDatabase::addDatabase(driver_type);
    database.setDatabaseName(db_name);
    database.setUserName(this->db_user);
    database.setPassword(this->db_pass);
    database.setHostName(this->db_hostname);
    return database;
}

void sql_database_manager::open_database()
{
    if( !database.open() )
    {
      qDebug() << database.lastError();
      qFatal( "Failed to connect." );
    }else{
      qDebug( "Connected!" );
    }
    database.transaction();
}


void sql_database_manager::set_dbname(std::string name)
{
    db_name=QString::fromStdString(name);
}

std::string sql_database_manager::get_dbname(void)
{
    return db_name.toStdString();
}


bool sql_database_manager::create_table(QString TABLE_CREATION_QUERY)
{
    bool success = false;
    if (database.isOpen())
    {
        QSqlQuery query(database);
        success = query.exec(TABLE_CREATION_QUERY);
        if(!success)
        {
            qDebug() << "create_table: "
                     << query.lastError();
        }
        else
        {
            database.commit();
        }
    }
    return success;

}

QSqlDatabase *sql_database_manager::get_db(void)
{
   return &database;
}
