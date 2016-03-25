#include "sql_database.h"
#include "acicd.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int main(void)
{
    sql_database BDD;

    QSqlDatabase db=BDD.create_database();
    BDD.open_database(db);

    ACICD acicd_object(&db,"acicd.csv");

 //   acicd_object.parse_ACICD();

    db.close();

    return 0;
}



