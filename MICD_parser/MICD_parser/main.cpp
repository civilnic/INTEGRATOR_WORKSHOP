#include <iostream>
#include <string>
#include <fstream>

#include "sql_database_manager.h"
#include "micd_document.h"

int main(int argc, char *argv[])
{
    const char *micd_name=argv[1];

    sql_database_manager *BDD;
    BDD= new sql_database_manager();
    std::cout << "Parametre programme (MICD): %s\n"<<micd_name<< std::endl;
    micd_document *MICD=new micd_document(BDD,micd_name);

    return 0;
}
