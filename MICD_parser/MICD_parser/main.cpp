#include <iostream>
#include <string>
#include <fstream>
#include <QString>

#include <xls.h>

using namespace std;
using namespace xls;

int main(void)
{
    xlsWorkBook *WorkBook;

    const char *micd_name="ICD_prim_a_1.xls";
    const char *characterSet="UTF-8";

    WorkBook=xls_open(micd_name,characterSet);

    return 0;
}
