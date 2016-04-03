#include "acicd_document.h"

#include "csv_parser.h"
#include "csv_stl_traits.h"
#include "csv_data.h"
#include <boost/optional/optional_io.hpp>
#include "boost/lexical_cast.hpp"

ACICD_DOCUMENT::ACICD_DOCUMENT(sql_database_manager *database_manager,QString filename)
{

    printf("creation objet ACICD\n");
    path_name=filename;
    BDD=database_manager;
    db=(*BDD).get_db();

    DB_FIELDS_ACICD = { { 2, "Name" },
                          { 3, "Path" },
                          { 4, "Micd" },
                          { 5, "Equipment" },
                          { 6, "Version" }
                        };

    DB_VALUES_ACICD["Name"]=path_name;
    DB_VALUES_ACICD["Path"]="";
    DB_VALUES_ACICD["Equipment"]=5;
    DB_VALUES_ACICD["Version"]="V4.5";



    if(BDD->create_table(DB_QUERY_CREATE_ACICD))
    {
        id=this->insert_acicd();
        db->commit();

    }
    else
    {
        printf("failed to create ACICD table\n");
    }

}

template<typename parser_>
void parsefile(std::fstream& f, parser_& parser)
{
    char buf[16192];
    while(f.good() && !parser.error())
    {
        int nb = sizeof(buf);
        f.read(buf, nb);
        if(!f.good())
            nb = f.gcount();

        for(int i = 0; i < nb; ++i)
        {
            parser.consume(buf[i]);
        }
    }
    if(f.eof())
        parser.end_of_data();
}




bool ACICD_DOCUMENT::parse_ACICD(void)
{
    dvp::csv_parser<dvp::csv_stl_traits> parser;
    dvp::csv_data data;
    dvp::acicd_data_handler handler(data, true, parser);

    std::fstream f(this->path_name.toStdString().c_str());

    if ( f.peek() == std::ifstream::traits_type::eof() )
    {
       // Empty File
      //std::cout << "The file "+this->path_name+" is empty" << std::endl;
       return false;
    }

    parsefile(f, parser);

    dvp::csv_data::const_iterator it;
    std::vector<std::string>::const_iterator it_record;
    acicd_data_section section;
    acicd_data_section previous_section=(acicd_data_section)0;
    int indice;

    std::map<int,std::string> DB_FIELDS_CONNECTOR = { { 2, "Type" },
                                                      { 3, "Name" },
                                                      { 4, "Pin" },
                                                      { 5, "Pin_Role" },
                                                      { 6, "Line_Type" }
                                                    };


    for(it=data.begin();it!=data.end();++it)
    {
       indice=boost::lexical_cast<int,std::string>((*it)[0]);
       section=(acicd_data_section)indice;

       if(section==acicd_data_section::EQUIPMENT)
       {
           if(section!=previous_section)
           {
              BDD->create_table(DB_QUERY_CREATE_EQUIPMENT);
           }

           acicd_equipment *equipment_obj=new acicd_equipment(BDD);

           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(equipment_obj->DB_FIELDS_EQUIPMENT.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        equipment_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
           }

           equipment_obj->insert_equipment();
           free(equipment_obj);
       }

//       if(section==acicd_data_section::CONNECTOR)
//       {
//           std::cout <<(*it)[0] << std::endl;

//           std::string query_field="INSERT INTO CONNECTOR (" ;
//           std::string query_values="VALUES (" ;

//           for(it_record=it->begin();it_record!=it->end();++it_record)
//           {

//               if(DB_FIELDS_CONNECTOR.count(it_record-it->begin())==1)
//               {
//                    if((*it_record).empty()!=1)
//                    {
//                        query_field+=", \'"+DB_FIELDS_CONNECTOR[it_record-it->begin()]+"\'";
//                        query_values+=", \'"+*it_record+"\'";

//                        std::cout << it_record-it->begin()   << std::endl;
//                        std::cout <<"test nasa:" +   *it_record   << std::endl;
//                    }
//               }
//           }
//           Query2DB(db,query_field,query_values);
//       }
       previous_section=section;
    }
    (*db).commit();
    return true;
}


int ACICD_DOCUMENT::insert_acicd(void)
{
    int Id = -1;
    bool success = false;

    if (db->isOpen())
    {
        Id=this->is_acicd_exist(DB_VALUES_ACICD["Name"]);

        // acicd is not in DB
        if(Id==0)
        {
            // NULL = is the keyword for the autoincrement to generate next value

            QSqlQuery query(*db);
            query.prepare(insert_query);

            query.bindValue(":"+DB_FIELDS_ACICD[2], DB_VALUES_ACICD[DB_FIELDS_ACICD[2]]);
            query.bindValue(":"+DB_FIELDS_ACICD[3], DB_VALUES_ACICD[DB_FIELDS_ACICD[3]]);
            query.bindValue(":"+DB_FIELDS_ACICD[4], DB_VALUES_ACICD[DB_FIELDS_ACICD[4]]);
            query.bindValue(":"+DB_FIELDS_ACICD[5], DB_VALUES_ACICD[DB_FIELDS_ACICD[5]]);
            query.bindValue(":"+DB_FIELDS_ACICD[6], DB_VALUES_ACICD[DB_FIELDS_ACICD[6]]);

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
            std::cout << DB_VALUES_ACICD["Name"].toStdString() + " already exists in db with: " << std::endl;
            printf("Id: %d\n",Id);
        }
    }

    return Id;
}

int ACICD_DOCUMENT::is_acicd_exist(QString Name)
{
    bool success = false;
    if (db->isOpen())
    {
        QSqlQuery query(*db);

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
bool ACICD_DOCUMENT::delete_acicd(int id)
{
    bool success = false;
    if (db->isOpen())
    {
        QSqlQuery query(*db);

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
            db->commit();
        }

    }
    return success;
}
