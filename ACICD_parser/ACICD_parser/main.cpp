#include <iostream>
#include <string>
#include <fstream>

#include "csv_parser.h"
#include "csv_stl_traits.h"
#include "csv_data.h"


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
            std::cout << buf[i];
        }
    }
    if(f.eof())
        parser.end_of_data();
}

int main(int argc, char** argv)
{
    std::string file;
    if(argc <= 1)
            file = "acicd.csv";
        else
            file = argv[1];
    dvp::csv_parser<dvp::csv_stl_traits> parser;
    handler<std::string> h(parser);
    std::fstream f(file);
    parsefile(f, parser);
    std::cout << h.nbfields
//			data.size()
            << " " << h.nblines
            << std::endl;
    return 0;
}

