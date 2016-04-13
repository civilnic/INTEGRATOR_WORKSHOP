#include "acicd_element.h"

acicd_element::acicd_element(sql_database_manager *database_manager)
{
    update_query.clear();

    id=-1;
    BDD=database_manager;
    db=(*BDD).get_db();
}

bool acicd_element::set_parameters(int field,std::string value)
{

    DB_VALUES[QString::fromStdString(DB_FIELDS[field])]=QString::fromStdString(value);
    return true;
}

bool acicd_element::modify_parameters(std::map<int,std::string> DB_NEW_FIELDS)
{
    id=-1;
    DB_FIELDS=DB_NEW_FIELDS;
    return true;
}

QString acicd_element::get_value(QString field)
{
    return DB_VALUES[field];
}


void acicd_element::create_update_query(QString field)
{
    update_query=QString("UPDATE %1 SET %2=:%2 WHERE (id=:id)").arg(DB_table_name).arg(field);
}

int acicd_element::get_id(void)
{
    return id;
}

int acicd_element::is_element_exist(QString Name)
{
    bool success;
//    boost::unordered_map<std::string,int>::const_iterator got = Element_collection.find (Name);

//    if ( got == Element_collection.end() )
//    {
//        //std::cout << "["+DB_table_name.toStdString()+"} Element non trouve: ";
//       //      std::cout <<        Name<<std::endl;
//      return 0;
//    }
//    else
//    {
//       // std::cout << "["+DB_table_name.toStdString()+"} Element trouve identifiant: "+Name;
//       // printf("%d\n",got->second);

//      return got->second;
//    }

    if (db->isOpen())
    {
        QSqlQuery query(*db);

        query.prepare(test_query);
        query.bindValue(":test_field", Name);
        std::cout << "[is_element_exist] test_field: " << Name.toStdString() << std::endl;
        std::cout << "[is_element_exist] test_query: " << test_query.toStdString() << std::endl;
        BDD->sql_log_file << "[is_element_exist] test_field: " << Name <<endl;
        BDD->sql_log_file << "[is_element_exist] test_query: " << test_query <<endl;
        success=query.exec();

        if(!success)
        {
            qDebug() << "[is_element_exist]: "
                     << query.lastError();
            BDD->sql_log_file << "[is_element_exist]: "
                                 << query.lastError().text() <<endl;
        }
        else
        {

            query.first();

            if(query.isValid())
            {
                if(query.value("id")==0)
                {
                    return 0;
                }
                else
                {
                    return query.value("id").toInt();
                }
            }
            else
            {
                return 0;
            }
        }
    }
    return -1;
}


bool acicd_element::insert_intable(void)
{
//d    int Id = -1;
    bool success = false;

    if (db->isOpen())
    {
        id=this->is_element_exist(this->get_value(test_field));
        // NULL = is the keyword for the autoincrement to generate next value

        // element is not in DB
        if(id==0)
        {
            QSqlQuery query(*db);
            std::map<QString,QString>::iterator iterator;

            query.prepare(insert_query);

            for(iterator=(this->DB_VALUES).begin();iterator!=(this->DB_VALUES.end());++iterator)
            {
                 query.bindValue(":"+iterator->first, iterator->second);
            }

            success = query.exec();

            // Get database given autoincrement value
            if (success)
            {
                // http://www.sqlite.org/c3ref/last_insert_rowid.html
                id = query.lastInsertId().toInt();
                //Element_collection[this->get_value(test_field).toStdString()]=Id;
               // id=Id;
                return true;
            }
            else
            {
                BDD->sql_log_file <<"insert_acicd: "
                                    << query.lastError().text() <<endl;
                qDebug() << "insert_acicd: "
                         << query.lastError();
                return false;
            }
        }
        else
        {
            std::cout << "[insert_intable] [" + DB_table_name.toStdString() + "] element name: ["+this->get_value(test_field).toStdString() + "] already exists in db with: ";
            printf("Id: %d\n",id);

            BDD->sql_log_file << "[insert_intable] [" + DB_table_name + "] element name: ["+this->get_value(test_field) + "] already exists in db with: "
                              << "Id: " << id  <<endl;
            return false;
        }
    }


}


void acicd_element::set_reference(QString field,int ref_id)
{
    bool success = false;


    if (db->isOpen())
    {

        // acicd is not in DB
        if(id==-1)
        {
            std::cout << "[set_reference] [" + DB_table_name.toStdString() + "] is not in database, cannot reference element: ["+field.toStdString()+"]" << std::endl;
            BDD->sql_log_file << "[set_reference] [" + DB_table_name + "] is not in database, cannot reference element: ["+field+"]" <<endl;
        }
        else
        {

            // NULL = is the keyword for the autoincrement to generate next value

            QSqlQuery query(*db);
            std::cout << "[set_reference] [" + update_query.toStdString() + "] update_query" << std::endl;
            BDD->sql_log_file << "[set_reference] [" + update_query + "] update_query"  <<endl;
            this->create_update_query(field);
            std::cout << "[set_reference] [" + update_query.toStdString() + "] update_query" << std::endl;
            BDD->sql_log_file << "[set_reference] [" + update_query + "] update_query"  <<endl;
            query.prepare(update_query);

            query.bindValue(":id", id);

            const QString temp_string=QString(":")%field;
            std::cout << "[set_reference] [" + temp_string.toStdString() + "] temp_string" << std::endl;
            BDD->sql_log_file << "[set_reference] [" + temp_string + "] temp_string" <<endl;
            std::cout << "id:";std::cout << id<< std::endl;
            BDD->sql_log_file << "id:";BDD->sql_log_file << id<<endl;
            std::cout << "ref_id:";std::cout << ref_id<< std::endl;
            BDD->sql_log_file << "ref_id:";BDD->sql_log_file << ref_id<<endl;


            query.bindValue(temp_string, ref_id);

            success = query.exec();

            // Get database given autoincrement value
            if (!success)
            {
                BDD->sql_log_file << "set_reference: "<< query.lastError().text() <<endl;

                qDebug() << "set_reference: "
                         << query.lastError();
            }

        }
    }
}

void acicd_element::set_value(QString field,QString value)
{
    bool success = false;


    if (db->isOpen())
    {

        // acicd is not in DB
        if(id==-1)
        {
            std::cout << "[set_value] [" + DB_table_name.toStdString() + "] is not in database, cannot reference element: ["+field.toStdString()+"]" << std::endl;
            BDD->sql_log_file << "[set_value] [" + DB_table_name + "] is not in database, cannot reference element: ["+field+"]" <<endl;
        }
        else
        {

            // NULL = is the keyword for the autoincrement to generate next value

            QSqlQuery query(*db);
            std::cout << "[set_value] [" + update_query.toStdString() + "] update_query" << std::endl;
            BDD->sql_log_file << "[set_value] [" + update_query + "] update_query"  <<endl;
            this->create_update_query(field);
            std::cout << "[set_value] [" + update_query.toStdString() + "] update_query" << std::endl;
            BDD->sql_log_file << "[set_value] [" + update_query + "] update_query"  <<endl;
            query.prepare(update_query);

            query.bindValue(":id", id);

            const QString temp_string=QString(":")%field;
            std::cout << "[set_value] [" + temp_string.toStdString() + "] temp_string" << std::endl;
            BDD->sql_log_file << "[set_value] [" + temp_string + "] temp_string" <<endl;
            std::cout << "id:";std::cout << id<< std::endl;
            BDD->sql_log_file << "id:";BDD->sql_log_file << id <<endl;
            std::cout << "ref_id:";std::cout << value.toStdString()<< std::endl;
            BDD->sql_log_file << "ref_id:";BDD->sql_log_file << value <<endl;


            query.bindValue(temp_string, value);

            success = query.exec();

            // Get database given autoincrement value
            if (!success)
            {
                BDD->sql_log_file << "set_value: "<< query.lastError().text() <<endl;

                qDebug() << "set_value: "
                         << query.lastError();
            }

        }
    }
}
