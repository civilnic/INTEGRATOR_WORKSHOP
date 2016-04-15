#include "acicd_document.h"

#include "csv_parser.h"
#include "csv_stl_traits.h"
#include "csv_data.h"
#include <boost/optional/optional_io.hpp>
#include "boost/lexical_cast.hpp"

ACICD_DOCUMENT::ACICD_DOCUMENT(sql_database_manager *database_manager,QString filename)
{

    printf("creation objet ACICD\n");
    path_name=filename;
    BDD=database_manager;
    db=(*BDD).get_db();
    id=-1;

    DB_FIELDS_ACICD = { { 2, "Name" },
                          { 3, "Path" },
                          { 4, "Micd" },
                          { 5, "Equipment" },
                          { 6, "Version" }
                        };

    DB_VALUES_ACICD["Name"]=path_name;
    DB_VALUES_ACICD["Path"]="";
    DB_VALUES_ACICD["Equipment"]=5;
    DB_VALUES_ACICD["Version"]="V4.5";



    if(BDD->create_table(DB_QUERY_CREATE_ACICD))
    {
        db->transaction();
        id=this->insert_acicd();
        db->commit();

    }
    else
    {
        printf("failed to create ACICD table\n");
        BDD->sql_log_file << "failed to create ACICD table\n" <<endl;
    }




}

template<typename parser_>
void parsefile(std::fstream& f, parser_& parser)
{
    char buf[16192];
    while(f.good() && !parser.error())
    {
        int nb = sizeof(buf);
        f.read(buf, nb);
        if(!f.good())
            nb = f.gcount();

        for(int i = 0; i < nb; ++i)
        {
            parser.consume(buf[i]);
        }
    }
    if(f.eof())
        parser.end_of_data();
}




bool ACICD_DOCUMENT::parse_ACICD(void)
{
    dvp::csv_parser<dvp::csv_stl_traits> parser;
    dvp::csv_data data;
    dvp::acicd_data_handler handler(data, true, parser);

    std::fstream f(this->path_name.toStdString().c_str());

    if ( f.peek() == std::ifstream::traits_type::eof() )
    {
       // Empty File
      //std::cout << "The file "+this->path_name+" is empty" << std::endl;
       return false;
    }

    parsefile(f, parser);

    dvp::csv_data::const_iterator it;
    std::vector<std::string>::const_iterator it_record;
    acicd_data_section section;
    acicd_data_section previous_section=(acicd_data_section)0;
    int indice;

    acicd_equipment *equipment_obj=new acicd_equipment(BDD);
    acicd_connection_name *connection_name_obj=new acicd_connection_name(BDD);
    acicd_connector_line_type *connector_line_type_obj=new acicd_connector_line_type(BDD);
    acicd_connector_pin *connector_pin_obj=new acicd_connector_pin(BDD);
    acicd_connector_pin_role *connector_pin_role_obj=new acicd_connector_pin_role(BDD);
    acicd_connector *connector_obj=new acicd_connector(BDD);
    acicd_AFDX_TX_port *AFDX_TX_port_obj=new acicd_AFDX_TX_port(BDD);
    acicd_afdx_port_type *AFDX_port_type_obj=new acicd_afdx_port_type(BDD);
    acicd_afdx_port_characteristic *AFDX_port_characteristic_obj=new acicd_afdx_port_characteristic(BDD);
    acicd_afdx_port_transmission_type *AFDX_port_transmission_type_obj=new acicd_afdx_port_transmission_type(BDD);
    acicd_afdx_VL *AFDX_VL_obj=new acicd_afdx_VL(BDD);
    acicd_afdx_message *AFDX_MESSAGE_obj=new acicd_afdx_message(BDD);
    acicd_afdx_message_type *AFDX_MESSAGE_TYPE_obj=new acicd_afdx_message_type(BDD);
    acicd_afdx_application *AFDX_APPLICATION_obj=new acicd_afdx_application(BDD);

    acicd_afdx_FDS *AFDX_FDS_obj=new acicd_afdx_FDS(BDD);
    acicd_afdx_FS *AFDX_FS_obj=new acicd_afdx_FS(BDD);
    acicd_afdx_parameter *AFDX_PARAMETER_obj=new acicd_afdx_parameter(BDD);
    acicd_data_type *AFDX_DATA_TYPE_obj=new acicd_data_type(BDD);
    acicd_keyword *AFDX_KEYWORD_obj=new acicd_keyword(BDD);





    db->transaction();




    for(it=data.begin();it!=data.end();++it)
    {
       indice=boost::lexical_cast<int,std::string>((*it)[0]);
       section=(acicd_data_section)indice;

       if(section==acicd_data_section::EQUIPMENT)
       {
           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(equipment_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        equipment_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
           }

           if(equipment_obj->insert_intable())
           {
                this->set_equipment_reference(equipment_obj->get_id());
               equipment_obj->set_reference(QString("ACICD"),id);
           }
       }

       if(section==acicd_data_section::CONNECTOR)
       {

           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(connector_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        connector_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(connection_name_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        connection_name_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(connector_line_type_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        connector_line_type_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(connector_pin_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        connector_pin_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(connector_pin_role_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        connector_pin_role_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
           }

           if(connector_obj->insert_intable())
           {
                connector_obj->set_reference(QString("ACICD"),id);
                connector_obj->set_reference(QString("Equipment"),equipment_obj->get_id());
           }

           connection_name_obj->insert_intable();
           connector_line_type_obj->insert_intable();
           connector_pin_role_obj->insert_intable();

           if(connector_pin_obj->insert_intable())
           {
                connector_pin_obj->set_reference(QString("Connector_pin_role"),connector_pin_role_obj->get_id());
                connector_pin_obj->set_reference(QString("Connection_name"),connection_name_obj->get_id());
                connector_pin_obj->set_reference(QString("Line_type"),connector_line_type_obj->get_id());
                connector_pin_obj->set_reference(QString("Connector"),connector_obj->get_id());
                connector_pin_obj->set_reference(QString("ACICD"),id);
           }

       }

       if(section==acicd_data_section::AFDX_OUTPUT_VL)
       {
           connector_pin_obj->modify_parameters({ { 2, "Physical_Id" },{ 3, "Physical_speed" },{ 4, "Connector_pin" },{ 6, "Network_id" }});

           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(AFDX_TX_port_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_TX_port_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(AFDX_port_type_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_port_type_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(AFDX_port_characteristic_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_port_characteristic_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(AFDX_port_transmission_type_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_port_transmission_type_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(connector_pin_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        connector_pin_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(AFDX_VL_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_VL_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }

           }

           if(AFDX_VL_obj->insert_intable())
           {
               AFDX_VL_obj->set_reference(QString("ACICD"),id);
               AFDX_VL_obj->set_reference(QString("EQUIPMENT"),equipment_obj->get_id());
           }

           if(!connector_pin_obj->insert_intable())
           {
                connector_pin_obj->set_value(QString("Physical_Id"),connector_pin_obj->DB_VALUES["Physical_Id"]);
                connector_pin_obj->set_value(QString("Physical_speed"),connector_pin_obj->DB_VALUES["Physical_speed"]);
                connector_pin_obj->set_value(QString("Network_id"),connector_pin_obj->DB_VALUES["Network_id"]);
           }

           AFDX_port_type_obj->insert_intable();
           AFDX_port_characteristic_obj->insert_intable();
           AFDX_port_transmission_type_obj->insert_intable();

           if(AFDX_TX_port_obj->insert_intable())
           {
                AFDX_TX_port_obj->set_reference(QString("ACICD"),id);
                AFDX_TX_port_obj->set_reference(QString("EQUIPMENT"),equipment_obj->get_id());
                AFDX_TX_port_obj->set_reference(QString("Type"),AFDX_port_type_obj->get_id());
                AFDX_TX_port_obj->set_reference(QString("characteristic"),AFDX_port_characteristic_obj->get_id());
                AFDX_TX_port_obj->set_reference(QString("transmission_type"),AFDX_port_transmission_type_obj->get_id());
                AFDX_TX_port_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
           }
       }


       if(section==acicd_data_section::AFDX_OUTPUT_MESSAGE)
       {
           AFDX_VL_obj->modify_parameters({{ 5, "VL_name" }});
           AFDX_TX_port_obj->modify_parameters({ { 6, "TX_AFDX_port_Identifier" }});


           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(AFDX_MESSAGE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_MESSAGE_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(AFDX_MESSAGE_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_MESSAGE_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(AFDX_APPLICATION_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_APPLICATION_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(AFDX_VL_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_VL_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(AFDX_TX_port_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_TX_port_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }





               if(AFDX_FDS_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_FDS_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(AFDX_FS_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_FS_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(AFDX_PARAMETER_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_PARAMETER_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(AFDX_DATA_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_DATA_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
               if(AFDX_KEYWORD_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    if((*it_record).empty()!=1)
                    {
                        AFDX_KEYWORD_obj->set_parameters(it_record-it->begin(),*it_record);
                    }
               }
           }

         AFDX_VL_obj->insert_intable();

         if(AFDX_MESSAGE_obj->insert_intable())
         {

            AFDX_TX_port_obj->insert_intable();
            AFDX_MESSAGE_TYPE_obj->insert_intable();
            AFDX_APPLICATION_obj->insert_intable();

            AFDX_MESSAGE_obj->set_reference(QString("ACICD"),id);
            AFDX_MESSAGE_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
            AFDX_MESSAGE_obj->set_reference(QString("AFDX_TX_PORT"),AFDX_TX_port_obj->get_id());
            AFDX_MESSAGE_obj->set_reference(QString("AFDX_MESSAGE_TYPE"),AFDX_MESSAGE_TYPE_obj->get_id());
            AFDX_MESSAGE_obj->set_reference(QString("AFDX_APPLICATION"),AFDX_APPLICATION_obj->get_id());
         }


         if(AFDX_FDS_obj->insert_intable())
         {
            AFDX_FS_obj->insert_intable();

            if(AFDX_PARAMETER_obj->insert_intable())
            {
                AFDX_DATA_TYPE_obj->insert_intable();
                AFDX_KEYWORD_obj->insert_intable();
            }

            AFDX_FDS_obj->set_reference(QString("ACICD"),id);
            AFDX_FDS_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
            AFDX_FDS_obj->set_reference(QString("AFDX_MESSAGE"),AFDX_MESSAGE_obj->get_id());
            AFDX_FDS_obj->set_reference(QString("AFDX_FS"),AFDX_FS_obj->get_id());

            AFDX_FS_obj->set_reference(QString("ACICD"),id);
            AFDX_FS_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
            AFDX_FS_obj->set_reference(QString("AFDX_MESSAGE"),AFDX_MESSAGE_obj->get_id());
            AFDX_FS_obj->set_reference(QString("AFDX_FDS"),AFDX_FDS_obj->get_id());


            AFDX_PARAMETER_obj->set_reference(QString("ACICD"),id);
            AFDX_PARAMETER_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
            AFDX_PARAMETER_obj->set_reference(QString("AFDX_MESSAGE"),AFDX_MESSAGE_obj->get_id());
            AFDX_PARAMETER_obj->set_reference(QString("AFDX_FDS"),AFDX_FDS_obj->get_id());
            AFDX_PARAMETER_obj->set_reference(QString("DATA_TYPE"),AFDX_DATA_TYPE_obj->get_id());
            AFDX_PARAMETER_obj->set_reference(QString("KEYWORD"),AFDX_KEYWORD_obj->get_id());
         }



       }

       previous_section=section;
    }
    db->commit();
    return true;
}


int ACICD_DOCUMENT::insert_acicd(void)
{
    int Id = -1;
    bool success = false;

    if (db->isOpen())
    {
        Id=this->is_acicd_exist(DB_VALUES_ACICD["Name"]);

        // acicd is not in DB
        if(Id==0)
        {
            // NULL = is the keyword for the autoincrement to generate next value

            QSqlQuery query(*db);
            query.prepare(insert_query);

            query.bindValue(":"+DB_FIELDS_ACICD[2], DB_VALUES_ACICD[DB_FIELDS_ACICD[2]]);
            query.bindValue(":"+DB_FIELDS_ACICD[3], DB_VALUES_ACICD[DB_FIELDS_ACICD[3]]);
            query.bindValue(":"+DB_FIELDS_ACICD[4], DB_VALUES_ACICD[DB_FIELDS_ACICD[4]]);
            query.bindValue(":"+DB_FIELDS_ACICD[5], DB_VALUES_ACICD[DB_FIELDS_ACICD[5]]);
            query.bindValue(":"+DB_FIELDS_ACICD[6], DB_VALUES_ACICD[DB_FIELDS_ACICD[6]]);

            success = query.exec();

            // Get database given autoincrement value
            if (success)
            {
                // http://www.sqlite.org/c3ref/last_insert_rowid.html
                Id = query.lastInsertId().toInt();
            }
            else
            {
                BDD->sql_log_file << "insert_acicd: "<< query.lastError().text() <<endl;
                qDebug() << "insert_acicd: "
                         << query.lastError();
            }
        }
        else
        {
            std::cout << DB_VALUES_ACICD["Name"].toStdString() + " already exists in db with: " << std::endl;
            printf("Id: %d\n",Id);
            BDD->sql_log_file << QString(DB_VALUES_ACICD["Name"]) + " already exists in db with: " <<endl;
            BDD->sql_log_file << "Id: " <<Id <<endl;
        }
    }

    return Id;
}

int ACICD_DOCUMENT::set_equipment_reference(int equipment_id)
{
    int Id = -1;
    bool success = false;

    if (db->isOpen())
    {

        // acicd is not in DB
        if(id==-1)
        {
            std::cout << "[set_equipment_reference] acicd is not in database, cannot reference equipement " << std::endl;
            return -1;
        }
        else
        {

            // NULL = is the keyword for the autoincrement to generate next value

            QSqlQuery query(*db);
            query.prepare(update_equipment_query);

            query.bindValue(":id", id);
            query.bindValue(":Equipment", equipment_id);

            success = query.exec();

            // Get database given autoincrement value
            if (success)
            {
                // http://www.sqlite.org/c3ref/last_insert_rowid.html
                Id = query.lastInsertId().toInt();
            }
            else
            {
                BDD->sql_log_file <<"insert_acicd: "
                                     << query.lastError().text()<<endl;
                qDebug() << "insert_acicd: "
                         << query.lastError();
            }

        }
    }

    return Id;
}


int ACICD_DOCUMENT::is_acicd_exist(QString Name)
{
    bool success = false;
    if (db->isOpen())
    {
        QSqlQuery query(*db);

        query.prepare("SELECT id, Name FROM ACICD WHERE Name = (:name)");
        query.bindValue(":name", Name);

        success=query.exec();

        if(!success)
        {
            qDebug() << "is_acicd_exist: "
                     << query.lastError();
        }
        else
        {
            // on first valid record
            query.first();

            // record is valid
            if(query.isValid())
            {
                // number of matching record = 0 => acicd is not in db
                if(query.value("id")==0)
                {
                    return 0;
                }

                // acicd is already in db
                else
                {
                    return query.value("id").toInt();
                }
            }
            // record is not valid => query.first failed => no entry in db => acicd is not in db
            else
            {
                return 0;
            }
        }
    }
    return -1;
}
bool ACICD_DOCUMENT::delete_acicd(int id)
{
    bool success = false;
    if (db->isOpen())
    {
        QSqlQuery query(*db);

        query.prepare("DELETE FROM ACICD WHERE Id = (:id)");
        query.bindValue(":id", id);

        success=query.exec();

        if(!success)
        {
            BDD->sql_log_file <<"delete_acicd: "
                                 << query.lastError().text()<<endl;
            qDebug() << "delete_acicd: "
                     << query.lastError();
        }
        else
        {
            db->commit();
        }

    }
    return success;
}
