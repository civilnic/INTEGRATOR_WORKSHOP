#include "acicd.h"

ACICD::ACICD(QSqlDatabase db,std::string path_name)
{
    this->path_name=path_name;
    this->db=db;
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


bool ACICD::parse_ACICD(void)
{
    dvp::csv_parser<dvp::csv_stl_traits> parser;
    dvp::csv_data data;
    dvp::acicd_data_handler handler(data, true, parser);

    std::fstream f(this->path_name.c_str());

    if ( f.peek() == std::ifstream::traits_type::eof() )
    {
       // Empty File
       std::cout << "The file "+this->path_name+" is empty" << std::endl;
       return false;
    }

    parsefile(f, parser);

    return true;
}

bool ACICD::ACICD2DB(void)
{
    dvp::csv_data::const_iterator it;
    std::vector<std::string>::const_iterator it_record;
    acicd_data_section section;
    int indice;

    std::map<int,std::string> DB_FIELDS_EQUIPMENT = { { 2, "Name" },
                                                      { 3, "Description" },
                                                      { 4, "Type" },
                                                      { 5, "EMC Protection" },
                                                      { 6, "Zone" }
                                                    };
    std::map<int,std::string> DB_FIELDS_CONNECTOR = { { 2, "Type" },
                                                      { 3, "Name" },
                                                      { 4, "Pin" },
                                                      { 5, "Pin_Role" },
                                                      { 6, "Line_Type" }
                                                    };



    QSqlQuery query(db);
    query.prepare(DB_QUERY_CREATE_ACICD);
    if( !query.exec() )
    qDebug() << query.lastError();
    else
    qDebug() << "Table created!";

    query.prepare(DB_QUERY_CREATE_EQUIPMENT);
    if( !query.exec() )
    qDebug() << query.lastError();
    else
    qDebug() << "Table created!";


    query.prepare(DB_QUERY_CREATE_CONNECTOR);
    if( !query.exec() )
    qDebug() << query.lastError();
    else
    qDebug() << "Table created!";



    query.prepare(DB_QUERY_CREATE_Connector_Line_type);
    if( !query.exec() )
    qDebug() << query.lastError();
    else
    qDebug() << "Table created!";

    query.prepare(DB_QUERY_CREATE_Connector_Pin_Role);
    if( !query.exec() )
    qDebug() << query.lastError();
    else
    qDebug() << "Table created!";

    query.prepare(DB_QUERY_CREATE_Connection_Name);
    if( !query.exec() )
    qDebug() << query.lastError();
    else
    qDebug() << "Table created!";




















    for(it=data.begin();it!=data.end();++it)
    {
       indice=boost::lexical_cast<int,std::string>((*it)[0]);
       section=(acicd_data_section)indice;

       if(section==acicd_data_section::EQUIPMENT)
       {
           std::string query_field="INSERT INTO EQUIPMENT (" ;
           std::string query_values="VALUES (" ;

           for(it_record=it->begin();it_record!=it->end();++it_record)
           {

               if(DB_FIELDS_EQUIPMENT.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        query_field+=", \'"+DB_FIELDS_EQUIPMENT[it_record-it->begin()]+"\'";
                        query_values+=", \'"+*it_record+"\'";

//                        std::cout << it_record-it->begin()   << std::endl;
//                        std::cout <<"test nasa:" +   *it_record   << std::endl;
                    }
               }
           }
           Query2DB(db,query_field,query_values);
       }

       if(section==acicd_data_section::CONNECTOR)
       {
 //          std::cout <<(*it)[0] << std::endl;

           std::string query_field="INSERT INTO CONNECTOR (" ;
           std::string query_values="VALUES (" ;

           for(it_record=it->begin();it_record!=it->end();++it_record)
           {

               if(DB_FIELDS_CONNECTOR.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        query_field+=", \'"+DB_FIELDS_CONNECTOR[it_record-it->begin()]+"\'";
                        query_values+=", \'"+*it_record+"\'";

//                        std::cout << it_record-it->begin()   << std::endl;
//                        std::cout <<"test nasa:" +   *it_record   << std::endl;
                    }
               }
           }
           Query2DB(db,query_field,query_values);
       }
    }
}
