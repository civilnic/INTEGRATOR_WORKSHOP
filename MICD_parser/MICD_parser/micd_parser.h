#ifndef MICD_PARSER_H
#define MICD_PARSER_H

#include <iostream>
#include <xls.h>
#include <boost/algorithm/string.hpp>

#include "micd_header.h"

using namespace std;
using namespace xls;

class micd_parser
{
public:
    micd_parser(const char * filename);
};

#endif // MICD_PARSER_H
