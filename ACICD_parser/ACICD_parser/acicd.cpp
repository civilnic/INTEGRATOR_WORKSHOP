#include "acicd.h"

#include "csv_parser.h"
#include "csv_stl_traits.h"
#include "csv_data.h"
#include <boost/optional/optional_io.hpp>
#include "boost/lexical_cast.hpp"

ACICD::ACICD(sql_database_manager *BDD_,QString filename)
{
    printf("creation objet ACICD\n");
    path_name=filename;
    BDD=BDD_;
    db=(*BDD).get_db();

    if(BDD->create_acicd_table())
    {
        db_id=BDD->insert_acicd(path_name,"",0,5,"V4.5");
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




bool ACICD::parse_ACICD(void)
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
              BDD->create_equipment_table();
           }

           acicd_equipment *equipment_obj=new acicd_equipment();

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

           BDD->insert_equipment(equipment_obj);
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
