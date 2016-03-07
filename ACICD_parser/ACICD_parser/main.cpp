#include <iostream>
#include <string>
#include <fstream>

#include "csv_parser.h"
#include "csv_stl_traits.h"
#include "csv_data.h"
#include <boost/optional/optional_io.hpp>

#include "acicd_header.h"
#include "mysql_database.h"

#include <QtSql>
#define q2c(string) string.toStdString()

using namespace std;

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
           // std::cout << buf[i];
        }
    }
    if(f.eof())
        parser.end_of_data();
}

int main(int argc, char** argv)
{
    std::string file;

    dvp::csv_parser<dvp::csv_stl_traits> parser;

    //handler<std::string> h(parser);
    dvp::csv_data data;

    dvp::acicd_data_handler handler(data, true, parser);

    std::vector<std::string> vect_header;
    std::vector<std::string>::iterator it_header;

    if(argc <= 1)
            file = "acicd.csv";
        else
            file = argv[1];



    std::fstream f(file);

    parsefile(f, parser);
    std::cout << //h.nbfields
            data.size()
 //           << " " << h.nblines
            << std::endl;
//    int i=0;

//    dvp::csv_data::const_iterator it;
//    std::vector<std::string>::const_iterator it_record;


//    for(it=data.begin();it!=data.end();++it)
//    {
//       if((*it)[0].compare(key_word_begin_data_section)==0)
//       {
//            ++it;
//            std::cout <<(*it)[0] << std::endl;
//       }


//       for(it_record=it->begin();it_record!=it->end();++it_record)
//       {
//           // std::cout <<"test nasa:" +   *it_record   << std::endl;
//       }
//   }
    std::string db_name="INTEGRATOR_WORKSHOP";
    mysql_database BDD;
    QSqlDatabase db=BDD.set_database(db_name);

    if(db.open())

    {

        std::cout << "Vous etes maintenant connecte a "<< std::endl;
            std::cout       << q2c(db.hostName()) << std::endl;

        db.close();

    }

    else

    {

        std::cout << "La connexion a echouee" << std::endl;

    }

    return 0;
}

