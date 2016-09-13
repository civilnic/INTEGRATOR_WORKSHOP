#include <iostream>
#include <string>
#include <fstream>

#include "acicd_document.h"

using namespace std;


int main(int argc, char *argv[])
{
    sql_database_manager *BDD;
    BDD= new sql_database_manager();

    const char * acicd_name=argv[1];

    ACICD_DOCUMENT acicd(BDD,QString::fromStdString(acicd_name));

    acicd.parse_ACICD();


    return 0;
}



