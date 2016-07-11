#include <iostream>
#include <string>
#include <fstream>

#include "micd_parser.h"

int main(int argc, char *argv[])
{
    const char *micd_name=argv[1];

    micd_parser *MICD=new micd_parser(micd_name);

    return 0;
}
