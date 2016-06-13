#include <iostream>
#include <string>
#include <fstream>

#include "BasicExcel.h"

using namespace YExcel;
using namespace std;

int main(int argc, char *argv[])
{
    BasicExcel e;

    // Load a workbook with one sheet, display its contents and save into another file.
    e.Load("ICD_prim_a_1.xls");
    BasicExcelWorksheet* sheet1 = e.GetWorksheet("FUN_IN");
    if (sheet1)
    {
        size_t maxRows = sheet1->GetTotalRows();
        size_t maxCols = sheet1->GetTotalCols();
        cout << "Dimension of " << sheet1->GetAnsiSheetName() << " (" << maxRows << ", " << maxCols << ")" << endl;

        printf("          ");
        for (size_t c=0; c<maxCols; ++c) printf("%10d", c+1);
        cout << endl;

        for (size_t r=0; r<maxRows; ++r)
        {
            printf("%10d", r+1);
            for (size_t c=0; c<maxCols; ++c)
            {
                BasicExcelCell* cell = sheet1->Cell(r,c);
                switch (cell->Type())
                {
                    case BasicExcelCell::UNDEFINED:
                        printf("          ");
                        break;

                    case BasicExcelCell::INT:
                        printf("%10d", cell->GetInteger());
                        break;

                    case BasicExcelCell::DOUBLE:
                        printf("%10.6lf", cell->GetDouble());
                        break;

                    case BasicExcelCell::STRING:
                        printf("%10s", cell->GetString());
                        break;

                    case BasicExcelCell::WSTRING:
                        wprintf(L"%10s", cell->GetWString());
                        break;
                }
            }
            cout << endl;
        }
    }
    cout << endl;
    return 0;
}
