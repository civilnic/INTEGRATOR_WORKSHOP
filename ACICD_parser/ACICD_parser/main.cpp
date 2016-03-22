#include <string>
#include "sql_database.h"
#include "acicd.h"
#define q2c(string) string.toStdString()

using namespace std;


int main(void)
{
    sql_database BDD;

    QSqlDatabase db=BDD.create_database();
    BDD.open_database(db);

    ACICD acicd_object(db,"acicd.csv");

    acicd_object.parse_ACICD();
    acicd_object.create_ACICD_tables();
    acicd_object.ACICD2DB();

    db.close();
    return 0;
}



