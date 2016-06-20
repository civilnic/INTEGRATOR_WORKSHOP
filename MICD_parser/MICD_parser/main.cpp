#include <iostream>
#include <string>
#include <fstream>



int main(void)
{
    xlsWorkBook *WorkBook;
    xlsWorkSheet *WorkSheet;
    int i,t;
    struct st_row_data* row;

    const char *micd_name="F:\\Mes documents\\Nicolas\\Boulot\\Developpement\\INTEGRATOR_WORKSHOP\\MICD_parser\\MICD_parser\\ICD_prim_a_1.xls";

    WorkBook=xls_open(micd_name,"UTF-8");


        return 0;
}
