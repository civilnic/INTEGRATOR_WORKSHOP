#include <iostream>
#include <string>
#include <fstream>

#include "micd_document.h"
#include "sql_database_manager.h"

int main(int argc, char *argv[])
{
    const char *micd_name=argv[1];

    sql_database_manager *BDD;
    BDD= new sql_database_manager();

    micd_document *MICD=new micd_document(BDD,micd_name);

    return 0;
}
