#include <iostream>
#include <string>
#include <fstream>

#include <xls.h>

using namespace std;
using namespace xls;

int main(void)
{
    xlsWorkBook *WorkBook;
    xlsWorkSheet *WorkSheet;
    int i,t;
    struct st_row_data* row;

    const char *micd_name="F:\\Mes documents\\Nicolas\\Boulot\\Developpement\\INTEGRATOR_WORKSHOP\\MICD_parser\\MICD_parser\\ICD_prim_a_1.xls";

    WorkBook=xls_open(micd_name,"UTF-8");

    if (WorkBook!=NULL)
    {
        for (i=0;i<WorkBook->sheets.count;i++)
            printf("Sheet N%i (%s) pos %i\n",i,WorkBook->sheets.sheet[i].name,WorkBook->sheets.sheet[i].filepos);


        WorkSheet=xls_getWorkSheet(WorkBook,3);

        xls_parseWorkSheet(WorkSheet);
        for (t=0;t<=WorkSheet->rows.lastrow;t++)
        {

        }
    }
    else
    {
        printf("Impossible d ouvrir %s\n",micd_name);
    }
        return 0;
}
