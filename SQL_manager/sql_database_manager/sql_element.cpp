#include "sql_element.h"

sql_element::sql_element(sql_database_manager *database_manager)
{
    update_query.clear();
    id=-1;

    BDD=database_manager;
    db=(*BDD).get_db();
}


bool sql_element::set_parameters(int field,std::string value)
{

    DB_VALUES[QString::fromStdString(DB_FIELDS[field])]=QString::fromStdString(value);
    return true;
}

bool sql_element::modify_parameters(std::map<int,std::string> DB_NEW_FIELDS)
{
    id=-1;
    DB_FIELDS=DB_NEW_FIELDS;
    return true;
}

QString sql_element::get_value(QString field)
{
    return DB_VALUES[field];
}


void sql_element::set_value(QString field,QString value)
{
    DB_VALUES[field]=value;
 //   std::cout << "[set_value] field: " << field.toStdString() << " value: " << value.toStdString() << value.toUInt() << std::endl;
}


void sql_element::create_update_query(QString field)
{
    update_query=QString("UPDATE %1 SET %2=:%2 WHERE (rowid=:rowid)").arg(DB_table_name).arg(field);
}

int sql_element::get_id(void)
{
    return id;
}

int sql_element::is_element_exist_new(int ref_sql_element)
{
    bool success;
    std::map<QString,QString>::iterator iterator;
    QSqlQuery query(*db);

    if (db->isOpen())
    {

        query.prepare(test_query);
        query.bindValue(sql_element_field, ref_sql_element);

        for(iterator=(this->DB_VALUES).begin();iterator!=(this->DB_VALUES.end());++iterator)
        {
            query.bindValue(":"+iterator->first, iterator->second);
//                BDD->sql_log_file << "[is_element_exist_new] champ: " << iterator->first << "[is_element_exist_new] valeur: " << iterator->second <<endl;

        }

//        std::cout << "[is_element_exist_new] test_query: " << test_query.toStdString() << std::endl;
//        BDD->sql_log_file << "[is_element_exist_new] test_query: " << test_query <<endl;
        success=query.exec();

        if(!success)
        {
//            qDebug() << "[is_element_exist_new]: "
//                     << query.lastError();
//            BDD->sql_log_file << "[is_element_exist_new]: "
//                                 << query.lastError().text() <<endl;
            return -1;
        }
        else
        {

            query.first();

            if(query.isValid())
            {
                if(query.value("rowid")==0)
                {
                    return 0;
                }
                else
                {
                    return query.value("rowid").toInt();
                }
            }
            else
            {
                return 0;
            }
        }
    }

}


bool sql_element::insert_intable_new(int ref_sql_element)
{

    bool success = false;
    QSqlQuery query(*db);
    std::map<QString,QString>::iterator iterator;



    if (db->isOpen())
    {
  //      BDD->sql_log_file <<"[insert_intable_new] before is_element_exist_new value: " << id <<endl;

        id=this->is_element_exist_new(ref_sql_element);

        // NULL = is the keyword for the autoincrement to generate next value
   //     BDD->sql_log_file <<"[insert_intable_new] return value: " << id <<endl;

        // element is not in DB
        if(id==0)
        {
            query.prepare(insert_query);
            query.bindValue(sql_element_field, ref_sql_element);

            for(iterator=(this->DB_VALUES).begin();iterator!=(this->DB_VALUES.end());++iterator)
            {
                 query.bindValue(":"+iterator->first, iterator->second);
   //              BDD->sql_log_file << "[insert_intable_new] champ: " << iterator->first << "   [insert_intable_new] valeur: " << iterator->second <<endl;

           }

            success = query.exec();

            // Get database given autoincrement value
            if (success)
            {
                // http://www.sqlite.org/c3ref/last_insert_rowid.html
                id = query.lastInsertId().toInt();
   //            BDD->sql_log_file <<"insert_intable_new: ajoute avec succes avec id=" << id  << query.lastError().text() <<endl;

                //Element_collection[this->get_value(test_field).toStdString()]=Id;
               // id=Id;
                return true;
            }
            else
            {
  //             BDD->sql_log_file <<"insert_intable_new: id=" << id <<endl
 //                               << query.lastQuery()<<endl
//                                  << query.lastError().text() <<endl;
//                qDebug() << "insert_intable_new: "
//                         << query.lastError();
                id=-1;
                return false;
            }
        }
        else
        {
  //          std::cout << "[insert_intable_new] [" + DB_table_name.toStdString() + "] element name: ["+this->get_value(test_field).toStdString() + "] already exists in db with: ";
  //         printf("Id: %d\n",id);

  //          BDD->sql_log_file << "[insert_intable_new] [" + DB_table_name + "] element name: ["+this->get_value(test_field) + "] already exists in db with: "
  //                            << "Id: " << id  <<endl;
            return false;
        }
    }
}



void sql_element::set_reference(QString field,int ref_id)
{
    bool success = false;


    if (db->isOpen())
    {

        // acicd is not in DB
        if(id==-1)
        {
//            std::cout << "[set_reference] [" + DB_table_name.toStdString() + "] is not in database, cannot reference element: ["+field.toStdString()+"]" << std::endl;
 //           BDD->sql_log_file << "[set_reference] [" + DB_table_name + "] is not in database, cannot reference element: ["+field+"]" <<endl;
        }
        else
        {

            // NULL = is the keyword for the autoincrement to generate next value

            QSqlQuery query(*db);
 //           std::cout << "[set_reference] [" + update_query.toStdString() + "] update_query" << std::endl;
 //           BDD->sql_log_file << "[set_reference] [" + update_query + "] update_query and id="<<id  <<endl;
            this->create_update_query(field);
 //           std::cout << "[set_reference] [" + update_query.toStdString() + "] update_query" << std::endl;
 //           BDD->sql_log_file << "[set_reference] [" + update_query + "] update_query"  <<endl;
            query.prepare(update_query);

            query.bindValue(":rowid", id);

            const QString temp_string=QString(":")%field;
//            std::cout << "[set_reference] [" + temp_string.toStdString() + "] temp_string" << std::endl;
//           BDD->sql_log_file << "[set_reference] [" + temp_string + "] temp_string" <<endl;
//            std::cout << "id:";std::cout << id<< std::endl;
//            BDD->sql_log_file << "id:" << id<<endl;
 //           std::cout << "ref_id:";std::cout << ref_id<< std::endl;
 //           BDD->sql_log_file << "ref_id:" << ref_id <<endl;


            query.bindValue(temp_string, ref_id);

            success = query.exec();

            // Get database given autoincrement value
            if (!success)
            {
                BDD->sql_log_file << "set_reference: "<< query.lastError().text() <<endl;

//                qDebug() << "set_reference: "
//                         << query.lastError();
            }

        }
    }
}

void sql_element::update_value(QString field,QString value)
{
    bool success = false;


    if (db->isOpen())
    {

        // acicd is not in DB
        if(id==-1)
        {
//            std::cout << "[set_value] [" + DB_table_name.toStdString() + "] is not in database, cannot reference element: ["+field.toStdString()+"]" << std::endl;
//            BDD->sql_log_file << "[set_value] [" + DB_table_name + "] is not in database, cannot reference element: ["+field+"]" <<endl;
        }
        else
        {

            // NULL = is the keyword for the autoincrement to generate next value

            QSqlQuery query(*db);
//            std::cout << "[set_value] [" + update_query.toStdString() + "] update_query" << std::endl;
//            BDD->sql_log_file << "[set_value] [" + update_query + "] update_query"  <<endl;
            this->create_update_query(field);
//            std::cout << "[set_value] [" + update_query.toStdString() + "] update_query" << std::endl;
//            BDD->sql_log_file << "[set_value] [" + update_query + "] update_query"  <<endl;
            query.prepare(update_query);

            query.bindValue(":id", id);

            const QString temp_string=QString(":")%field;
 //           std::cout << "[set_value] [" + temp_string.toStdString() + "] temp_string" << std::endl;
 //           BDD->sql_log_file << "[set_value] [" + temp_string + "] temp_string" <<endl;
 //           std::cout << "id:";std::cout << id<< std::endl;
 //          BDD->sql_log_file << "id:";BDD->sql_log_file << id <<endl;
 //           std::cout << "ref_id:";std::cout << value.toStdString()<< std::endl;
 //           BDD->sql_log_file << "ref_id:";BDD->sql_log_file << value <<endl;


            query.bindValue(temp_string, value);

            success = query.exec();

            // Get database given autoincrement value
            if (!success)
            {
 //               BDD->sql_log_file << "set_value: "<< query.lastError().text() <<endl;

//                qDebug() << "set_value: "
//                         << query.lastError();
            }

        }
    }
}
