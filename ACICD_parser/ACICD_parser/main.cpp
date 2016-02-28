#include <iostream>
#include <string>
#include <fstream>

#include "csv_parser.h"
#include "csv_stl_traits.h"
#include "csv_data.h"
#include <boost/optional/optional_io.hpp>

#include "acicd_header.h"

using namespace std;


template<typename string_type>
struct handler
{
    int curfield = 0;
    int nbfields = 0;
    int nblines = 0;
    bool field_handler(string_type const &/*f*/) {
        nbfields += 1;
        return true;
    }

    bool line_handler() { nblines += 1; curfield = 0; return true;}
    template<typename parser_>
    handler(parser_ &parser)
    {
        parser.field_handler = [this](string_type const& s) { return this->field_handler(s); };
        parser.end_line_handler = [this]() { return this->line_handler(); };
    }
};

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

    dvp::csv_data_handler handler(data, false, parser);

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
    int i=0;

    dvp::csv_data::const_iterator it;
    std::vector<std::string>::const_iterator it_record;

    // const std::string chaine="header1";
    // std::cout <<(*it)[chaine]   << std::endl;
//    vect_header=data.headers();

//    for(it_header=vect_header.begin();it_header!=vect_header.end();++it_header)
//    {
       // std::cout << *it_header  << std::endl;
//    }

    for(it=data.begin();it!=data.end();++it)
    {
       //std::cout <<(*it)[0] << std::endl;
       std::string str_header{*(it->begin()),*(it->end())};
        std::cout << str_header << std::endl;

       for(it_record=it->begin();it_record!=it->end();++it_record)
       {
           // std::cout <<"test nasa:" +   *it_record   << std::endl;
       }
    }

    return 0;
}

