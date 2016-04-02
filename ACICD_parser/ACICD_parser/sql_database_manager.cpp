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
    int Id = -1;
    bool success = false;

    if (database.isOpen())
    {
        Id=this->is_acicd_exist(Name);

        // acicd is not in DB
        if(Id==0)
        {
            // NULL = is the keyword for the autoincrement to generate next value

            QSqlQuery query(database);
            query.prepare("INSERT INTO ACICD VALUES(NULL,:Name,:Path,:Micd,:Equipment,:Version)");

            query.bindValue(":Name", Name);
            query.bindValue(":Path", Path);
            query.bindValue(":Micd", Micd);
            query.bindValue(":Equipment", Equipment);
            query.bindValue(":Version", Version);

            success = query.exec();

            // Get database given autoincrement value
            if (success)
            {
                // http://www.sqlite.org/c3ref/last_insert_rowid.html
                Id = query.lastInsertId().toInt();
            }
            else
            {
                qDebug() << "insert_acicd: "
                         << query.lastError();
            }
        }
        else
        {
            std::cout << Name.toStdString() + " already exists in db with: " << std::endl;
            printf("Id: %d\n",Id);
        }
    }

    return Id;
}

int sql_database_manager::insert_equipment(acicd_equipment *equipment)
{
    int Id = -1;
    bool success = false;

    if (database.isOpen())
    {
        Id=this->is_equipment_exist(equipment->get_name());
        // NULL = is the keyword for the autoincrement to generate next value

        // equipment is not in DB
        if(Id==0)
        {
            QSqlQuery query(database);
            std::map<QString,QString>::iterator iterator;

            query.prepare("INSERT INTO EQUIPMENT VALUES(NULL,:Name,:Description,:Type,:EMC_Protection,:Zone,:FIN)");

            for(iterator=(equipment->DB_FIELDS_VALUES).begin();iterator!=(equipment->DB_FIELDS_VALUES.end());++iterator)
            {
                 query.bindValue(":"+iterator->first, iterator->second);
            }

            success = query.exec();

            // Get database given autoincrement value
            if (success)
            {
                // http://www.sqlite.org/c3ref/last_insert_rowid.html
                Id = query.lastInsertId().toInt();
            }
            else
            {
                qDebug() << "insert_acicd: "
                         << query.lastError();
            }
        }
        else
        {
            std::cout << equipment->get_name().toStdString() + " already exists in db with: " << std::endl;
            printf("Id: %d\n",Id);
        }
    }

    return Id;
}



int sql_database_manager::is_acicd_exist(QString Name)
{
    bool success = false;
    if (database.isOpen())
    {
        QSqlQuery query(database);

        query.prepare("SELECT id, Name FROM ACICD WHERE Name = (:name)");
        query.bindValue(":name", Name);

        success=query.exec();

        if(!success)
        {
            qDebug() << "is_acicd_exist: "
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
                if(query.value("id")==0)
                {
                    return 0;
                }

                // acicd is already in db
                else
                {
                    return query.value("id").toInt();
                }
            }
            // record is not valid => query.first failed => no entry in db => acicd is not in db
            else
            {
                return 0;
            }
        }
    }
    return -1;
}


int sql_database_manager::is_equipment_exist(QString Name)
{
    bool success = false;
    if (database.isOpen())
    {
        QSqlQuery query(database);

        query.prepare("SELECT id, Name FROM EQUIPMENT WHERE Name = (:name)");
        query.bindValue(":name", Name);


        success=query.exec();

        if(!success)
        {
            qDebug() << "is_equipement_exist: "
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
                if(query.value("id")==0)
                {
                    return 0;
                }

                // acicd is already in db
                else
                {
                    return query.value("id").toInt();
                }
            }
            // record is not valid => query.first failed => no entry in db => acicd is not in db
            else
            {
                return 0;
            }
        }
    }
    return -1;
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

bool sql_database_manager::create_equipment_table(void)
{

    // Create table "EQUIPMENT"
    bool success = false;
    if (database.isOpen())
    {
        QSqlQuery query(database);
        success = query.exec(DB_QUERY_CREATE_EQUIPMENT);
        if(!success)
        {
            qDebug() << "create_equipment_table: "
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
