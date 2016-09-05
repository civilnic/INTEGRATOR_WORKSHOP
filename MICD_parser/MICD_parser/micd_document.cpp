#include "micd_document.h"
#include "micd_header.h"

micd_document::micd_document(sql_database_manager *database_manager,const char * filename)
{

    int i;
    WORD t,tt;

    xlsRow* row;
    xlsRow* header;

    xlsWorkBook *WorkBook;
    xlsWorkSheet *WorkSheet;

    string sheet_name;
    string header_test_string;

    WorkBook=xls_open(filename,"UTF-8");

    if (WorkBook!=NULL)
    {
        for (i=0;i<WorkBook->sheets.count;i++)
        {
            sheet_name=std::string((char *)WorkBook->sheets.sheet[i].name);
            printf("Sheet N%i (%s) pos %i\n",i,WorkBook->sheets.sheet[i].name,WorkBook->sheets.sheet[i].filepos);

            if(sheet_name.compare("FUN_IN")==0)
            {
                WorkSheet=xls_getWorkSheet(WorkBook,i);

                xls_parseWorkSheet(WorkSheet);
                printf("Count of rows: %i\n",WorkSheet->rows.lastrow + 1);
                printf("Max col: %i\n",WorkSheet->rows.lastcol);

                //header=xls_row(WorkSheet,0);
                header=&WorkSheet->rows.row[0];
                for (tt=0;tt<=WorkSheet->rows.lastcol;tt++)
                {
                    xlsCell	*cell;
                    cell = &header->cells.cell[tt];
                    if(cell->id == 0x201) continue;
                    string temp=std::string((char *)cell->str);

                    /* string convert in lower case */
                    boost::algorithm::to_lower(temp);

                    /* delete all spaces from string */
                    boost::algorithm::erase_all(temp," ");

                    header_test_string+=temp;
                }

                std::cout <<header_test_string << std::endl<< std::endl;

                std::vector<std::string> vector_test=MICD_header_FUN_IN_type2;
                string test=boost::algorithm::join(vector_test,"");
                boost::algorithm::to_lower(test);
                boost::algorithm::erase_all(test," ");
                std::cout <<test << std::endl;


                for (t=0;t<=WorkSheet->rows.lastrow;t++)
                {
                    row=&WorkSheet->rows.row[t];
                    //xls::xls_showROW(row);
                    for (tt=0;tt<=WorkSheet->rows.lastcol;tt++)
                    {
                        xlsCell	*cell;
                        cell = &row->cells.cell[tt];


                        if(cell->id == 0x201) continue;
                        //xls_showCell(&cell);
                        //std::cout << cell->str << std::endl;
                    }
                }
             }
         }
    }
    else
    {
        printf("Impossible d ouvrir %s\n",filename);
    }
}
