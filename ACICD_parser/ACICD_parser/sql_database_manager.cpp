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
    bool success = false;

    if (database.isOpen())
    {
        // NULL = is the keyword for the autoincrement to generate next value

        QSqlQuery query(database);
        success = query.exec(QString("INSERT INTO ACICD VALUES(NULL,'%1','%2',%3,%4,'%5')").arg(Name).arg(Path).arg(Micd).arg(Equipment).arg(Version));

        // Get database given autoincrement value
        if (success)
        {
            // http://www.sqlite.org/c3ref/last_insert_rowid.html
            newId = query.lastInsertId().toInt();
        }
        else
        {
            qDebug() << "insert_acicd: "
                     << query.lastError();
        }

    }

    return newId;
}

bool sql_database_manager::is_acicd_exist(QString Name)
{
    bool success = false;
    if (database.isOpen())
    {
        QSqlQuery query(database);

        query.prepare("SELECT Name FROM ACICD WHERE Name = (:name)");
        query.bindValue(":name", Name);


        success=query.exec();

        if(!success)
        {
            qDebug() << "delete_acicd: "
                     << query.lastError();
        }
        else
        {
            // on first valid record
            query.first();

            // record is valid
            if(query.isValid())
            {
                // number of matching record = 0 => acicd is not in db
                if(query.value(0)==0)
                {
                 success=false;
                }

                // acicd is already in db
                else
                {
                 success=true;
                }
            }
            // record is not valid => query.first failed => no entry in db => acicd is not in db
            else
            {
                success=false;
            }
        }
    }
    return success;
}


bool sql_database_manager::delete_acicd(int id)
{
    bool success = false;
    if (database.isOpen())
    {
        QSqlQuery query(database);

        query.prepare("DELETE FROM ACICD WHERE Id = (:id)");
        query.bindValue(":id", id);

        success=query.exec();

        if(!success)
        {
            qDebug() << "delete_acicd: "
                     << query.lastError();
        }
        else
        {
            database.commit();
        }

    }
    return success;
}

bool sql_database_manager::create_acicd_table(void)
{

    // Create table "ACICD"
    bool success = false;
    if (database.isOpen())
    {
        QSqlQuery query(database);
        success = query.exec(DB_QUERY_CREATE_ACICD);
        if(!success)
        {
            qDebug() << "create_acicd_table: "
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
