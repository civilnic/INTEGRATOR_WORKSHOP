#include "acicd_element.h"

acicd_element::acicd_element(sql_database_manager *database_manager)
{

}

bool acicd_element::set_parameters(int field,std::string value)
{

    DB_VALUES[QString::fromStdString(DB_FIELDS[field])]=QString::fromStdString(value);
    return true;
}

QString acicd_element::get_name(void)
{
    return DB_VALUES["Name"];
}

int acicd_element::get_id(void)
{
    return id;
}

int acicd_element::is_element_exist(QString Name)
{
    bool success = false;
    if (db->isOpen())
    {
        QSqlQuery query(*db);

        query.prepare(test_query);
        query.bindValue(":test_field", Name);


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
                // number of matching record = 0 => is not in db
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
            // record is not valid => query.first failed => no entry in db => is not in db
            else
            {
                return 0;
            }
        }
    }
    return -1;
}


int acicd_element::insert_intable(void)
{
    int Id = -1;
    bool success = false;

    if (db->isOpen())
    {
        Id=this->is_element_exist(this->get_name());
        // NULL = is the keyword for the autoincrement to generate next value

        // equipment is not in DB
        if(Id==0)
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
            std::cout << this->get_name().toStdString() + " already exists in db with: " << std::endl;
            printf("Id: %d\n",Id);
        }
    }

    return Id;
}
