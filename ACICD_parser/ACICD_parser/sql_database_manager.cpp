#include "sql_database_manager.h"

sql_database_manager::sql_database_manager(void)
{
    log_file.setFileName("sql_log.txt");
    log_file.open(QIODevice::ReadWrite | QIODevice::Text);

    sql_log_file.setDevice(&log_file);


    sql_log_file <<"creation objet sql_database\n";
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
    QSqlQuery query(database);

    if( !database.open() )
    {
      qDebug() << database.lastError();
      sql_log_file << "Failed to connect.";
      qFatal( "Failed to connect." );
    }else{
      sql_log_file <<  "Connected!" <<endl;
      qDebug( "Connected!" );
    }

    query.prepare("PRAGMA synchronous=off");
    query.exec();
    query.prepare("PRAGMA journal_mode=off");
    query.exec();

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
            sql_log_file << "create_table: "  <<endl;
            sql_log_file << TABLE_CREATION_QUERY  <<endl;
            sql_log_file << query.lastError().text() <<endl;
            qDebug() << "create_table: " + TABLE_CREATION_QUERY
                     << query.lastError();
        }
        else
        {
            database.commit();
        }
    }
    return success;

}

bool sql_database_manager::execute_query(QString QUERY)
{
    bool success = false;
    if (database.isOpen())
    {
        QSqlQuery query(database);
        success = query.exec(QUERY);
        if(!success)
        {
            sql_log_file << "execute_query: "  <<endl;
            sql_log_file << QUERY  <<endl;
            sql_log_file << query.lastError().text() <<endl;
            qDebug() << "execute_query: " + QUERY
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
