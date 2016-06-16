#include "micd_parser.h"

micd_parser::micd_parser()
{
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
}
