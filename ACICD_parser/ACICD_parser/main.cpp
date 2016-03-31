#include "acicd.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int main(void)
{
    sql_database_manager *BDD;
    BDD= new sql_database_manager();

    QString acicd_name="acicd.csv";
    ACICD objet_acicd(BDD,acicd_name);

    objet_acicd.parse_ACICD();


    return 0;
}



