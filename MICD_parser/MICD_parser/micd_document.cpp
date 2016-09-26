#include "micd_document.h"
#include "micd_header.h"

micd_document::micd_document(sql_database_manager *database_manager,const char * filename)
{

    unsigned int i;
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

    std::map<QString,QString>::iterator iterator;


    printf("creation objet MICD\n");
    path_name=filename;
    BDD=database_manager;
    db=(*BDD).get_db();
    id_micd=-1;

    DB_FIELDS = {   { 2, "Name" },
                          { 3, "Path" },
                          { 4, "Modele" },
                          { 5, "Version" }
                        };

    DB_VALUES["Name"]=path_name;
    DB_VALUES["Path"]="";
    DB_VALUES["Model"]="prim_a";
    DB_VALUES["Version"]="V4.5";



    if(BDD->create_table(DB_QUERY_CREATE_TABLE))
    {
        db->transaction();
        id_micd=this->insert_micd();
        db->commit();

    }
    else
    {
        printf("failed to create MICD table\n");
        BDD->sql_log_file << "failed to create MICD table\n" <<endl;
    }


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
                    //    std::cout <<temp << std::endl;
                    }

                }

//                TODO: utiliser le header determiner plus haut pour parser les colonnes simulation level (dont le nombre varie suivant le template) et les colonnes suivantes


                //
                // loop on each line except the first one (already parsed) of the current tab
                //
                for (t=1;t<=WorkSheet->rows.lastrow;t++)
                {

                    // create a micd_port_in object
                    micd_port_in *Ports_in_obj=new micd_port_in(BDD);

                    micd_port_name *Ports_name_obj=new micd_port_name(BDD);
                    micd_data_type *Ports_type_obj=new micd_data_type(BDD);

                    row=&WorkSheet->rows.row[t];
                    //xls::xls_showROW(row);
                    //for (tt=0;tt<=WorkSheet->rows.lastcol;tt++)
                    for (tt=0;tt<16;tt++)
                    {
                        xlsCell	*cell=NULL;

                        cell = &row->cells.cell[tt];
                        if(cell->id == 0x201) continue;

                        std::string cell_value=std::string((char *)cell->str);

                        if(Ports_name_obj->DB_FIELDS.count((int)tt)==1)
                        {
                             if((cell_value.empty())!=1)
                             {
                                 Ports_name_obj->set_parameters((int)(tt),cell_value);
                             }
                        }
                        if(Ports_type_obj->DB_FIELDS.count((int)tt)==1)
                        {
                             if((cell_value.empty())!=1)
                             {
                                 Ports_type_obj->set_parameters((int)(tt),cell_value);
                             }
                        }


                       // Ports_in_obj->set_parameters((int)(tt),cell_value);


                        //xls_showCell(&cell);
                        //std::cout << "cellule:   " << tt << "  /  contenu: "<< cell->str << std::endl;
                    }

               //     Ports_name_obj->insert_intable_new(id_micd);
               //     Ports_type_obj->insert_intable_new(id_micd);

                    if(Ports_name_obj->insert_intable_new(id_micd))
                    {
                         Ports_in_obj->set_reference(QString("Name"),Ports_name_obj->get_id());
                    }


                    Ports_type_obj->insert_intable_new(id_micd);
                    Ports_in_obj->set_reference(QString("Type"),Ports_type_obj->get_id());

                    if(Ports_in_obj->insert_intable_new(id_micd))
                    {

                    }else
                    {
                        for(iterator=(Ports_in_obj->DB_VALUES).begin();iterator!=(Ports_in_obj->DB_VALUES.end());++iterator)
                        {
                             QString temp1=iterator->first;
                             QString temp2=iterator->second;

                             std::cout << "cellule:   " << temp1.toStdString() << std::endl;
                             std::cout << "  /  contenu: " << temp2.toStdString() << std::endl;
                        }
                        std::cout << "-------------------insertion KO" << std::endl;
                    }
                    db->commit();
                }

             }


         }
    }
    else
    {
        printf("Impossible d ouvrir %s\n",filename);
    }
}


int micd_document::insert_micd(void)
{
    int Id = -1;
    bool success = false;

    if (db->isOpen())
    {
 //       Id=this->is_acicd_exist(DB_VALUES_ACICD["Name"]);

        // acicd is not in DB
//        if(Id==0)
//        {
            // NULL = is the keyword for the autoincrement to generate next value

            QSqlQuery query(*db);
            query.prepare(insert_query);

            query.bindValue(":"+DB_FIELDS[2], DB_VALUES[DB_FIELDS[2]]);
            query.bindValue(":"+DB_FIELDS[3], DB_VALUES[DB_FIELDS[3]]);
            query.bindValue(":"+DB_FIELDS[4], DB_VALUES[DB_FIELDS[4]]);
            query.bindValue(":"+DB_FIELDS[5], DB_VALUES[DB_FIELDS[5]]);

            success = query.exec();

            // Get database given autoincrement value
            if (success)
            {
                // http://www.sqlite.org/c3ref/last_insert_rowid.html
                Id = query.lastInsertId().toInt();
            }
            else
            {
//                BDD->sql_log_file << "insert_acicd_test: "<< query.lastError().text() <<endl;
//                qDebug() << "insert_acicd_test: "
//                         << query.lastError();
            }
//        }
//        else
//        {
//            std::cout << DB_VALUES_ACICD["Name"].toStdString() + " already exists in db with: " << std::endl;
//            printf("Id: %d\n",Id);
//            BDD->sql_log_file << QString(DB_VALUES_ACICD["Name"]) + " already exists in db with: " <<endl;
//            BDD->sql_log_file << "Id: " <<Id <<endl;
//        }
    }

    return Id;
}
