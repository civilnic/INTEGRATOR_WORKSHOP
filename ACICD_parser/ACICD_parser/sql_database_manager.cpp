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

int sql_database_manager::insert_acicd(QString Name, QString Path, int Micd, int Equipment, QString Version)
{
    int newId = -1;
    bool ret = false;

    if (database.isOpen())
    {
        // NULL = is the keyword for the autoincrement to generate next value

        QSqlQuery query(database);
        ret = query.exec(QString("INSERT INTO ACICD VALUES(NULL,'%1','%2',%3,%4,'%5')").arg(Name).arg(Path).arg(Micd).arg(Equipment).arg(Version));

        // Get database given autoincrement value
        if (ret)
        {
            // http://www.sqlite.org/c3ref/last_insert_rowid.html
            newId = query.lastInsertId().toInt();
        }
        else
        {
            qDebug() << query.lastError();
        }

    }

    return newId;
}

bool sql_database_manager::is_acicd_exist(QString Name)
{
    bool ret = false;
    if (database.isOpen())
    {
        QSqlQuery query(database);
        query.exec(QString("SELECT * FROM ACICD WHERE Name=%1").arg(Name));
        printf("insert_acicd query.size(): %d\n",query.size());
        if(query.size()>1)
        {
            ret=true;
        }
        database.commit();
    }
    return ret;
}


bool sql_database_manager::delete_acicd(int id)
{
    bool ret = false;
    if (database.isOpen())
    {
        QSqlQuery query(database);
        ret = query.exec(QString("DELETE FROM ACICD WHERE ID=%1").arg(id));
        database.commit();

    }
    return ret;
}

bool sql_database_manager::create_acicd_table(void)
{

    // Create table "ACICD"
    bool ret = false;
    if (database.isOpen())
    {
        QSqlQuery query(database);
        ret = query.exec(DB_QUERY_CREATE_ACICD);
        database.commit();
    }
    return ret;

}


QSqlDatabase *sql_database_manager::get_db(void)
{
   return &database;
}
