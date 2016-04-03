#include <iostream>
#include <string>
#include <fstream>

#include "acicd_document.h"

using namespace std;


int main(void)
{
    sql_database_manager *BDD;
    BDD= new sql_database_manager();

    QString acicd_name="acicd.csv";
    ACICD_DOCUMENT acicd(BDD,acicd_name);

    acicd.parse_ACICD();


    return 0;
}



