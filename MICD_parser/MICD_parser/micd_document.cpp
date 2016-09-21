#include "micd_document.h"

micd_document::micd_document(sql_database_manager *database_manager,const char * filename)
{

    int i;
    WORD t,tt;

    xlsRow* row;
    xlsRow* header;

    xlsWorkBook *WorkBook;
    xlsWorkSheet *WorkSheet;

    xlsCell	*cell=NULL;

    string sheet_name("");
    string temp("");
    string header_test_string("");

    std::vector<std::string> *vector_test;

    WorkBook=xls_open(filename,"UTF-8");




    if (WorkBook!=NULL)
    {
        for (i=0;i<WorkBook->sheets.count;i++)
        {
            //
            // get and display sheet name
            //
            sheet_name=std::string((char *)WorkBook->sheets.sheet[i].name);
            printf("Sheet N%i (%s) pos %i\n",i,WorkBook->sheets.sheet[i].name,WorkBook->sheets.sheet[i].filepos);

            //
            //  If sheet name is equal to FUN_IN
            //

            if(sheet_name.compare("FUN_IN")==0)
            {
                //
                // get worksheet from workbook
                //

                WorkSheet=xls_getWorkSheet(WorkBook,i);

                //
                // parse worksheet
                //

                xls_parseWorkSheet(WorkSheet);

                //
                // Display rows & columns numbers
                //

                printf("Count of rows: %i\n",WorkSheet->rows.lastrow + 1);
                printf("Max col: %i\n",WorkSheet->rows.lastcol);

                //
                // Get first line = header
                //      _ Header type is xlsRow
                //      _ To determine MICD type, it will compared to several header type
                //      defined in micd_header.h
                //
                header=&WorkSheet->rows.row[0];

                //
                // loop on each col of first row
                // each cell has a specific type defined by libxls: xlsCell
                // Here we want to concantenate each cell value in lower case without space to be
                // compared to header string vectors from micd_header.h
                //
                for (tt=0;tt<=WorkSheet->rows.lastcol;tt++)
                {
                    //
                    // set cell pointer to current cell
                    //
                    cell = &header->cells.cell[tt];

                    //
                    // if cell is empty go to next cell;
                    //
                    if(cell->id == 0x201) continue;

                    //
                    // convert cell content into string
                    //
                    temp=std::string((char *)cell->str);

                    //
                    // string convert in lower case
                    //
                    boost::algorithm::to_lower(temp);

                    //
                    // delete all spaces from string
                    //
                    boost::algorithm::erase_all(temp," ");

                    //
                    // add temp string into concatenation header string
                    //
                    header_test_string+=temp;
                }

                // display complete header concatenation string
                std::cout <<header_test_string << std::endl<< std::endl;

                // ierate through test header vector (defined in micd_header.h)
                for(it_header_test = MICD_header_test.begin(); it_header_test!=MICD_header_test.end(); ++it_header_test)
                {
                    // string creation from itrator targetted vector
                    temp=boost::algorithm::join(*it_header_test,"");

                    // lower conversion
                    boost::algorithm::to_lower(temp);

                    // delete white space
                    boost::algorithm::erase_all(temp," ");

                    // compare with micd header test string
                    if(temp==header_test_string)
                    {
                        // save MICD header format into header_vector
                        vector_test=&(*it_header_test);

                        // TO BE REMOVED: check header vector
                        temp=boost::algorithm::join(*vector_test,"");
                        std::cout <<temp << std::endl;
                    }

                }


                micd_port_in *Ports_in_obj=new micd_port_in(BDD);

                for (t=1;t<=WorkSheet->rows.lastrow;t++)
                {
                    row=&WorkSheet->rows.row[t];
                    //xls::xls_showROW(row);
                    for (tt=0;tt<=WorkSheet->rows.lastcol;tt++)
                    {
                        xlsCell	*cell;
                        cell = &row->cells.cell[tt];
                        Ports_in_obj->set_parameters(tt,cell->str);

                        if(cell->id == 0x201) continue;
                        //xls_showCell(&cell);
                        //std::cout << cell->str << std::endl;
                    }
                    if(Ports_in_obj->insert_intable_new(id))
                    {
                        this->set_equipment_reference(Ports_in_obj->get_id());
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
