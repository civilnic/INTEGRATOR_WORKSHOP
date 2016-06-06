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

    DB_FIELDS_ACICD = {   { 2, "Name" },
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
    acicd_afdx_rx_port *AFDX_RX_port_obj=new acicd_afdx_rx_port(BDD);
    acicd_afdx_port_type *AFDX_port_type_obj=new acicd_afdx_port_type(BDD);
    acicd_afdx_port_characteristic *AFDX_port_characteristic_obj=new acicd_afdx_port_characteristic(BDD);
    acicd_afdx_port_transmission_type *AFDX_port_transmission_type_obj=new acicd_afdx_port_transmission_type(BDD);
    acicd_afdx_VL *AFDX_VL_obj=new acicd_afdx_VL(BDD);
    acicd_afdx_message *AFDX_MESSAGE_obj=new acicd_afdx_message(BDD);
    acicd_afdx_message_type *AFDX_MESSAGE_TYPE_obj=new acicd_afdx_message_type(BDD);
    acicd_application *APPLICATION_obj=new acicd_application(BDD);

    acicd_afdx_FDS *AFDX_FDS_obj=new acicd_afdx_FDS(BDD);
    acicd_afdx_FS *AFDX_FS_obj=new acicd_afdx_FS(BDD);
    acicd_afdx_parameter *AFDX_PARAMETER_obj=new acicd_afdx_parameter(BDD);
    acicd_data_type *DATA_TYPE_obj=new acicd_data_type(BDD);
    acicd_keyword *KEYWORD_obj=new acicd_keyword(BDD);
    acicd_afdx_signal *AFDX_SIGNAL_obj=new acicd_afdx_signal(BDD);
    acicd_afdx_signal_bool_charact *AFDX_SIGNAL_BOOL_DESC_obj=new acicd_afdx_signal_bool_charact(BDD);
    acicd_afdx_signal_type *AFDX_SIGNAL_TYPE_obj=new acicd_afdx_signal_type(BDD);

    acicd_afdx_signal_enumerate_charact *AFDX_SIGNAL_ENUMERATE_DESC_obj=new acicd_afdx_signal_enumerate_charact(BDD);
    acicd_afdx_signal_float_charact *AFDX_SIGNAL_FLOAT_DESC_obj=new acicd_afdx_signal_float_charact(BDD);
    acicd_afdx_signal_int_charact *AFDX_SIGNAL_INT_DESC_obj=new acicd_afdx_signal_int_charact(BDD);
    acicd_afdx_signal_opaque_charact *AFDX_SIGNAL_OPAQUE_DESC_obj=new acicd_afdx_signal_opaque_charact(BDD);
    acicd_afdx_signal_string_charact *AFDX_SIGNAL_STRING_DESC_obj=new acicd_afdx_signal_string_charact(BDD);
    acicd_unit *ACICD_UNIT_obj=new acicd_unit(BDD);

    acicd_a429_bus *A429_BUS_obj=new acicd_a429_bus(BDD);
    acicd_a429_label *A429_LABEL_obj=new acicd_a429_label(BDD);
    acicd_a429_label_type *A429_LABEL_TYPE_obj=new acicd_a429_label_type(BDD);
    acicd_a429_signal *A429_SIGNAL_obj=new acicd_a429_signal(BDD);
    acicd_a429_parameter *A429_PARAMETER_obj=new acicd_a429_parameter(BDD);
    acicd_a429_signal_type *A429_SIGNAL_TYPE_obj=new acicd_a429_signal_type(BDD);

    acicd_a429_signal_bool_charact *A429_SIGNAL_BOOL_DESC_obj=new acicd_a429_signal_bool_charact(BDD);
    acicd_a429_signal_enumerate_charact *A429_SIGNAL_ENUMERATE_DESC_obj=new acicd_a429_signal_enumerate_charact(BDD);
    acicd_a429_signal_float_charact *A429_SIGNAL_FLOAT_DESC_obj=new acicd_a429_signal_float_charact(BDD);
    acicd_a429_signal_int_charact *A429_SIGNAL_INT_DESC_obj=new acicd_a429_signal_int_charact(BDD);
    acicd_a429_signal_opaque_charact *A429_SIGNAL_OPAQUE_DESC_obj=new acicd_a429_signal_opaque_charact(BDD);
    acicd_a429_signal_string_charact *A429_SIGNAL_STRING_DESC_obj=new acicd_a429_signal_string_charact(BDD);

    acicd_ANA_line *ANA_LINE_obj=new acicd_ANA_line(BDD);
    acicd_ANA_parameter *ANA_PARAMETER_obj=new acicd_ANA_parameter(BDD);
    acicd_ANA_signal *ANA_SIGNAL_obj=new acicd_ANA_signal(BDD);


    acicd_description *DESCRIPTION_obj=new acicd_description(BDD);



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

           if(equipment_obj->insert_intable_new(id))
           {
               this->set_equipment_reference(equipment_obj->get_id());
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

           if(connector_obj->insert_intable_new(id))
           {
                connector_obj->set_reference(QString("Equipment"),equipment_obj->get_id());
           }

           connection_name_obj->insert_intable_new(id);
           connector_line_type_obj->insert_intable_new(id);
           connector_pin_role_obj->insert_intable_new(id);

           if(connector_pin_obj->insert_intable_new(id))
           {
                connector_pin_obj->set_reference(QString("Connector_pin_role"),connector_pin_role_obj->get_id());
                connector_pin_obj->set_reference(QString("Connection_name"),connection_name_obj->get_id());
                connector_pin_obj->set_reference(QString("Line_type"),connector_line_type_obj->get_id());
                connector_pin_obj->set_reference(QString("Connector"),connector_obj->get_id());
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

           if(!connector_pin_obj->insert_intable_new(id))
           {
                connector_pin_obj->update_value(QString("Physical_Id"),connector_pin_obj->DB_VALUES["Physical_Id"]);
                connector_pin_obj->update_value(QString("Physical_speed"),connector_pin_obj->DB_VALUES["Physical_speed"]);
                connector_pin_obj->update_value(QString("Network_id"),connector_pin_obj->DB_VALUES["Network_id"]);
           }

           if(AFDX_VL_obj->insert_intable_new(id))
           {
               AFDX_VL_obj->set_reference(QString("EQUIPMENT"),equipment_obj->get_id());
               AFDX_VL_obj->set_reference(QString("Connector_pin"),connector_pin_obj->get_id());
           }



           AFDX_port_type_obj->insert_intable_new(id);
           AFDX_port_characteristic_obj->insert_intable_new(id);
           AFDX_port_transmission_type_obj->insert_intable_new(id);

           if(AFDX_TX_port_obj->insert_intable_new(id))
           {
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
               if(DESCRIPTION_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
 //                   if((*it_record).empty()!=1)
//                    {
                        DESCRIPTION_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_MESSAGE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
 //                   if((*it_record).empty()!=1)
 //                   {
                        AFDX_MESSAGE_obj->set_parameters(it_record-it->begin(),*it_record);
 //                   }
               }
               if(AFDX_MESSAGE_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_MESSAGE_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
 //                   }
               }
               if(APPLICATION_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
 //                   if((*it_record).empty()!=1)
//                    {
                        APPLICATION_obj->set_parameters(it_record-it->begin(),*it_record);
 //                   }
               }
               if(AFDX_VL_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_VL_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_TX_port_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_TX_port_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }

               if(AFDX_FDS_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
 //                   if((*it_record).empty()!=1)
//                    {
                        AFDX_FDS_obj->set_parameters(it_record-it->begin(),*it_record);
 //                   }
               }
               if(AFDX_FS_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_FS_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_PARAMETER_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_PARAMETER_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(DATA_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
 //                   if((*it_record).empty()!=1)
 //                   {
                        DATA_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(KEYWORD_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        KEYWORD_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }

               if(AFDX_SIGNAL_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_SIGNAL_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_SIGNAL_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_SIGNAL_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_SIGNAL_BOOL_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_SIGNAL_BOOL_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_SIGNAL_STRING_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_SIGNAL_STRING_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_SIGNAL_ENUMERATE_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_SIGNAL_ENUMERATE_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_SIGNAL_FLOAT_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                   if((*it_record).empty()!=1)
//                    {
                        AFDX_SIGNAL_FLOAT_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_SIGNAL_INT_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_SIGNAL_INT_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_SIGNAL_OPAQUE_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_SIGNAL_OPAQUE_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(ACICD_UNIT_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
 //                   {
                        ACICD_UNIT_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
           }

         AFDX_VL_obj->insert_intable_new(id);

         if(AFDX_MESSAGE_obj->insert_intable_new(id))
         {

            AFDX_TX_port_obj->insert_intable_new(id);
            AFDX_MESSAGE_TYPE_obj->insert_intable_new(id);
            APPLICATION_obj->insert_intable_new(id);

            AFDX_MESSAGE_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
            AFDX_MESSAGE_obj->set_reference(QString("AFDX_TX_PORT"),AFDX_TX_port_obj->get_id());
            AFDX_MESSAGE_obj->set_reference(QString("AFDX_MESSAGE_TYPE"),AFDX_MESSAGE_TYPE_obj->get_id());
            AFDX_MESSAGE_obj->set_reference(QString("APPLICATION"),APPLICATION_obj->get_id());
         }


         if(AFDX_FDS_obj->insert_intable_new(id))
         {
            AFDX_FS_obj->insert_intable_new(id);

            AFDX_FDS_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
            AFDX_FDS_obj->set_reference(QString("AFDX_MESSAGE"),AFDX_MESSAGE_obj->get_id());
            AFDX_FDS_obj->set_reference(QString("AFDX_FS"),AFDX_FS_obj->get_id());

            AFDX_FS_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
            AFDX_FS_obj->set_reference(QString("AFDX_MESSAGE"),AFDX_MESSAGE_obj->get_id());
            AFDX_FS_obj->set_reference(QString("AFDX_FDS"),AFDX_FDS_obj->get_id());
         }

         if(AFDX_PARAMETER_obj->insert_intable_new(id))
         {
             DATA_TYPE_obj->insert_intable_new(id);
             KEYWORD_obj->insert_intable_new(id);

             AFDX_PARAMETER_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
             AFDX_PARAMETER_obj->set_reference(QString("AFDX_MESSAGE"),AFDX_MESSAGE_obj->get_id());
             AFDX_PARAMETER_obj->set_reference(QString("AFDX_FDS"),AFDX_FDS_obj->get_id());
             AFDX_PARAMETER_obj->set_reference(QString("type"),DATA_TYPE_obj->get_id());
             AFDX_PARAMETER_obj->set_reference(QString("keyword"),KEYWORD_obj->get_id());
         }

         if(AFDX_SIGNAL_obj->insert_intable_new(id))
         {
            ACICD_UNIT_obj->insert_intable_new(id);

            AFDX_SIGNAL_BOOL_DESC_obj->insert_intable_new(id);
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_SIGNAL_BOOL_DESC"),AFDX_SIGNAL_BOOL_DESC_obj->get_id());

            AFDX_SIGNAL_STRING_DESC_obj->insert_intable_new(id);
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_SIGNAL_STRING_DESC"),AFDX_SIGNAL_STRING_DESC_obj->get_id());

            AFDX_SIGNAL_ENUMERATE_DESC_obj->insert_intable_new(id);
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_SIGNAL_ENUMERATE_DESC"),AFDX_SIGNAL_ENUMERATE_DESC_obj->get_id());

            AFDX_SIGNAL_FLOAT_DESC_obj->insert_intable_new(id);
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_SIGNAL_FLOAT_DESC"),AFDX_SIGNAL_FLOAT_DESC_obj->get_id());

            AFDX_SIGNAL_INT_DESC_obj->insert_intable_new(id);

            AFDX_SIGNAL_obj->set_reference(QString("AFDX_SIGNAL_INT_DESC"),AFDX_SIGNAL_INT_DESC_obj->get_id());

            AFDX_SIGNAL_OPAQUE_DESC_obj->insert_intable_new(id);

            AFDX_SIGNAL_obj->set_reference(QString("AFDX_SIGNAL_OPAQUE_DESC"),AFDX_SIGNAL_OPAQUE_DESC_obj->get_id());


            AFDX_SIGNAL_TYPE_obj->insert_intable_new(id);

            AFDX_SIGNAL_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_MESSAGE"),AFDX_MESSAGE_obj->get_id());
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_FDS"),AFDX_FDS_obj->get_id());
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_PARAMETER"),AFDX_PARAMETER_obj->get_id());
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_FS"),AFDX_FS_obj->get_id());
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_SIGNAL_TYPE"),AFDX_SIGNAL_TYPE_obj->get_id());
         }
       }


       if(section==acicd_data_section::AFDX_INPUT_VL)
       {
           AFDX_VL_obj->modify_parameters({ { 8, "VL_Identifier" },{ 9, "VL_name" },{ 11, "BAG" },{ 12, "MAX_frame_size" }});
           connector_pin_obj->modify_parameters({ { 2, "Physical_Id" },{ 3, "Physical_speed" },{ 4, "Connector_pin" },{ 6, "Network_id" }});
           AFDX_port_type_obj->modify_parameters({ { 18, "Name" } });

           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(AFDX_RX_port_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
  //                  if((*it_record).empty()!=1)
  //                  {
                        AFDX_RX_port_obj->set_parameters(it_record-it->begin(),*it_record);
  //                  }
               }
               if(AFDX_port_type_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
 //                   {
                        AFDX_port_type_obj->set_parameters(it_record-it->begin(),*it_record);
//                   }
               }
               if(AFDX_port_characteristic_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
 //                   if((*it_record).empty()!=1)
 //                   {
                        AFDX_port_characteristic_obj->set_parameters(it_record-it->begin(),*it_record);
 //                   }
               }
               if(AFDX_port_transmission_type_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
 //                   {
                        AFDX_port_transmission_type_obj->set_parameters(it_record-it->begin(),*it_record);
 //                   }
               }
               if(connector_pin_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        connector_pin_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_VL_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
 //                  if((*it_record).empty()!=1)
 //                   {
                        AFDX_VL_obj->set_parameters(it_record-it->begin(),*it_record);
 //                   }
               }
           }

           if(!connector_pin_obj->insert_intable_new(id))
           {
                connector_pin_obj->update_value(QString("Physical_Id"),connector_pin_obj->DB_VALUES["Physical_Id"]);
                connector_pin_obj->update_value(QString("Physical_speed"),connector_pin_obj->DB_VALUES["Physical_speed"]);
                connector_pin_obj->update_value(QString("Network_id"),connector_pin_obj->DB_VALUES["Network_id"]);
           }

           if(AFDX_VL_obj->insert_intable_new(id))
           {
               AFDX_VL_obj->set_reference(QString("EQUIPMENT"),equipment_obj->get_id());
               AFDX_VL_obj->set_reference(QString("Connector_pin"),connector_pin_obj->get_id());
           }



           AFDX_port_type_obj->insert_intable_new(id);
           AFDX_port_characteristic_obj->insert_intable_new(id);
           AFDX_port_transmission_type_obj->insert_intable_new(id);

           if(AFDX_RX_port_obj->insert_intable_new(id))
           {
                AFDX_RX_port_obj->set_reference(QString("EQUIPMENT"),equipment_obj->get_id());
                AFDX_RX_port_obj->set_reference(QString("Type"),AFDX_port_type_obj->get_id());
                AFDX_RX_port_obj->set_reference(QString("characteristic"),AFDX_port_characteristic_obj->get_id());
                AFDX_RX_port_obj->set_reference(QString("transmission_type"),AFDX_port_transmission_type_obj->get_id());
                AFDX_RX_port_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
           }

       }

       if(section==acicd_data_section::AFDX_INPUT_MESSAGE)
       {
           AFDX_VL_obj->modify_parameters({{ 5, "VL_name" }});
           AFDX_RX_port_obj->modify_parameters({ { 6, "RX_AFDX_port_Identifier" }});


           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(AFDX_MESSAGE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
 //                   if((*it_record).empty()!=1)
  //                  {
                        AFDX_MESSAGE_obj->set_parameters(it_record-it->begin(),*it_record);
 //                   }
               }
               if(AFDX_MESSAGE_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
 //                   if((*it_record).empty()!=1)
 //                   {
                        AFDX_MESSAGE_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
 //                   }
               }
               if(APPLICATION_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        APPLICATION_obj->set_parameters(it_record-it->begin(),*it_record);
//                   }
               }
               if(AFDX_VL_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
 //                   if((*it_record).empty()!=1)
//                    {
                        AFDX_VL_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_RX_port_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_RX_port_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }

               if(AFDX_FDS_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_FDS_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_FS_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_FS_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_PARAMETER_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_PARAMETER_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(DATA_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        DATA_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(KEYWORD_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        KEYWORD_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }

               if(AFDX_SIGNAL_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
 //                   if((*it_record).empty()!=1)
 //                   {
                        AFDX_SIGNAL_obj->set_parameters(it_record-it->begin(),*it_record);
 //                   }
               }
               if(AFDX_SIGNAL_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
  //                  if((*it_record).empty()!=1)
  //                  {
                        AFDX_SIGNAL_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
  //                  }
               }
               if(AFDX_SIGNAL_BOOL_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_SIGNAL_BOOL_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_SIGNAL_STRING_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_SIGNAL_STRING_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_SIGNAL_ENUMERATE_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_SIGNAL_ENUMERATE_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_SIGNAL_FLOAT_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                   if((*it_record).empty()!=1)
//                    {
                        AFDX_SIGNAL_FLOAT_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_SIGNAL_INT_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_SIGNAL_INT_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(AFDX_SIGNAL_OPAQUE_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
//                    if((*it_record).empty()!=1)
//                    {
                        AFDX_SIGNAL_OPAQUE_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
//                    }
               }
               if(ACICD_UNIT_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
 //                   if((*it_record).empty()!=1)
 //                   {
                        ACICD_UNIT_obj->set_parameters(it_record-it->begin(),*it_record);
 //                   }
               }
           }

         AFDX_VL_obj->insert_intable_new(id);

         if(AFDX_MESSAGE_obj->insert_intable_new(id))
         {

            AFDX_RX_port_obj->insert_intable_new(id);
            AFDX_MESSAGE_TYPE_obj->insert_intable_new(id);
            APPLICATION_obj->insert_intable_new(id);

            AFDX_MESSAGE_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
            AFDX_MESSAGE_obj->set_reference(QString("AFDX_RX_PORT"),AFDX_RX_port_obj->get_id());
            AFDX_MESSAGE_obj->set_reference(QString("AFDX_MESSAGE_TYPE"),AFDX_MESSAGE_TYPE_obj->get_id());
            AFDX_MESSAGE_obj->set_reference(QString("AFDX_APPLICATION"),APPLICATION_obj->get_id());
         }


         if(AFDX_FDS_obj->insert_intable_new(id))
         {
            AFDX_FS_obj->insert_intable_new(id);

            AFDX_FDS_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
            AFDX_FDS_obj->set_reference(QString("AFDX_MESSAGE"),AFDX_MESSAGE_obj->get_id());
            AFDX_FDS_obj->set_reference(QString("AFDX_FS"),AFDX_FS_obj->get_id());

            AFDX_FS_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
            AFDX_FS_obj->set_reference(QString("AFDX_MESSAGE"),AFDX_MESSAGE_obj->get_id());
            AFDX_FS_obj->set_reference(QString("AFDX_FDS"),AFDX_FDS_obj->get_id());
         }

         if(AFDX_PARAMETER_obj->insert_intable_new(id))
         {
             DATA_TYPE_obj->insert_intable_new(id);
             KEYWORD_obj->insert_intable_new(id);

             AFDX_PARAMETER_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
             AFDX_PARAMETER_obj->set_reference(QString("AFDX_MESSAGE"),AFDX_MESSAGE_obj->get_id());
             AFDX_PARAMETER_obj->set_reference(QString("AFDX_FDS"),AFDX_FDS_obj->get_id());
             AFDX_PARAMETER_obj->set_reference(QString("type"),DATA_TYPE_obj->get_id());
             AFDX_PARAMETER_obj->set_reference(QString("keyword"),KEYWORD_obj->get_id());
         }

         if(AFDX_SIGNAL_obj->insert_intable_new(id))
         {
            ACICD_UNIT_obj->insert_intable_new(id);

  //             AFDX_SIGNAL_FLOAT_DESC_obj->set_value(QString("unit"),QString::number(ACICD_UNIT_obj->get_id()));
  //             AFDX_SIGNAL_INT_DESC_obj->set_value(QString("unit"),QString::number(ACICD_UNIT_obj->get_id()));

            AFDX_SIGNAL_BOOL_DESC_obj->insert_intable_new(id);
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_SIGNAL_BOOL_DESC"),AFDX_SIGNAL_BOOL_DESC_obj->get_id());

            AFDX_SIGNAL_STRING_DESC_obj->insert_intable_new(id);
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_SIGNAL_STRING_DESC"),AFDX_SIGNAL_STRING_DESC_obj->get_id());

            AFDX_SIGNAL_ENUMERATE_DESC_obj->insert_intable_new(id);
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_SIGNAL_ENUMERATE_DESC"),AFDX_SIGNAL_ENUMERATE_DESC_obj->get_id());

            AFDX_SIGNAL_FLOAT_DESC_obj->insert_intable_new(id);

 //               ACICD_UNIT_obj->insert_intable_new(id);
 //              AFDX_SIGNAL_FLOAT_DESC_obj->set_value(QString("unit"),ACICD_UNIT_obj->get_id());
 //               AFDX_SIGNAL_FLOAT_DESC_obj->set_reference(QString("unit"),ACICD_UNIT_obj->get_id());
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_SIGNAL_FLOAT_DESC"),AFDX_SIGNAL_FLOAT_DESC_obj->get_id());

            AFDX_SIGNAL_INT_DESC_obj->insert_intable_new(id);

//                ACICD_UNIT_obj->insert_intable_new(id);
//                AFDX_SIGNAL_INT_DESC_obj->set_value(QString("unit"),QString(ACICD_UNIT_obj->get_id()));
//                AFDX_SIGNAL_INT_DESC_obj->set_reference(QString("unit"),ACICD_UNIT_obj->get_id());
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_SIGNAL_INT_DESC"),AFDX_SIGNAL_INT_DESC_obj->get_id());

            AFDX_SIGNAL_OPAQUE_DESC_obj->insert_intable_new(id);

            AFDX_SIGNAL_obj->set_reference(QString("AFDX_SIGNAL_OPAQUE_DESC"),AFDX_SIGNAL_OPAQUE_DESC_obj->get_id());


            AFDX_SIGNAL_TYPE_obj->insert_intable_new(id);

            AFDX_SIGNAL_obj->set_reference(QString("AFDX_VL"),AFDX_VL_obj->get_id());
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_MESSAGE"),AFDX_MESSAGE_obj->get_id());
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_FDS"),AFDX_FDS_obj->get_id());
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_PARAMETER"),AFDX_PARAMETER_obj->get_id());
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_FS"),AFDX_FS_obj->get_id());
            AFDX_SIGNAL_obj->set_reference(QString("AFDX_SIGNAL_TYPE"),AFDX_SIGNAL_TYPE_obj->get_id());
         }
       }


       if(section==acicd_data_section::A429_OUTPUT_BUS)
       {

           connector_pin_obj->modify_parameters({ { 8, "Connector_pin" } });

           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(connector_pin_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        connector_pin_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_BUS_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_BUS_obj->set_parameters(it_record-it->begin(),*it_record);
               }
           }

           connector_pin_obj->insert_intable_new(id);

           if(A429_BUS_obj->insert_intable_new(id))
           {
               A429_BUS_obj->set_reference(QString("EQUIPMENT"),equipment_obj->get_id());
               A429_BUS_obj->set_reference(QString("Connector_pin"),connector_pin_obj->get_id());
           }
       }

       if(section==acicd_data_section::A429_OUTPUT_LABEL)
       {
           A429_BUS_obj->modify_parameters({ { 5, "Name" } });
           DATA_TYPE_obj->modify_parameters({ { 27, "Name" } });
           KEYWORD_obj->modify_parameters({ { 34, "Name" } });

           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(APPLICATION_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        APPLICATION_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_BUS_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_BUS_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_LABEL_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_LABEL_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_LABEL_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_LABEL_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_PARAMETER_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_PARAMETER_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(DATA_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        DATA_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(KEYWORD_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        KEYWORD_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_BOOL_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_BOOL_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_ENUMERATE_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_ENUMERATE_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_FLOAT_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_FLOAT_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_INT_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_INT_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_OPAQUE_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_OPAQUE_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_STRING_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_STRING_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
               }

           }
           A429_BUS_obj->insert_intable_new(id);

           if(A429_LABEL_obj->insert_intable_new(id))
           {              
               APPLICATION_obj->insert_intable_new(id);
               A429_LABEL_TYPE_obj->insert_intable_new(id);

               A429_LABEL_obj->set_reference(QString("A429_BUS"),A429_BUS_obj->get_id());
               A429_LABEL_obj->set_reference(QString("APPLICATION"),APPLICATION_obj->get_id());
               A429_LABEL_obj->set_reference(QString("type"),A429_LABEL_TYPE_obj->get_id());
           }

           if(A429_PARAMETER_obj->insert_intable_new(id))
           {
               DATA_TYPE_obj->insert_intable_new(id);
               KEYWORD_obj->insert_intable_new(id);

               A429_PARAMETER_obj->set_reference(QString("A429_BUS"),A429_BUS_obj->get_id());
               A429_PARAMETER_obj->set_reference(QString("A429_LABEL"),A429_LABEL_obj->get_id());
               A429_PARAMETER_obj->set_reference(QString("type"),DATA_TYPE_obj->get_id());
               A429_PARAMETER_obj->set_reference(QString("keyword"),KEYWORD_obj->get_id());
           }

           if(A429_SIGNAL_obj->insert_intable_new(id))
           {

              A429_SIGNAL_BOOL_DESC_obj->insert_intable_new(id);
              A429_SIGNAL_obj->set_reference(QString("A429_SIGNAL_BOOL_DESC"),A429_SIGNAL_BOOL_DESC_obj->get_id());

              A429_SIGNAL_STRING_DESC_obj->insert_intable_new(id);
              A429_SIGNAL_obj->set_reference(QString("A429_SIGNAL_STRING_DESC"),A429_SIGNAL_STRING_DESC_obj->get_id());

              A429_SIGNAL_ENUMERATE_DESC_obj->insert_intable_new(id);
              A429_SIGNAL_obj->set_reference(QString("A429_SIGNAL_ENUMERATE_DESC"),A429_SIGNAL_ENUMERATE_DESC_obj->get_id());

              A429_SIGNAL_FLOAT_DESC_obj->insert_intable_new(id);
              A429_SIGNAL_obj->set_reference(QString("A429_SIGNAL_FLOAT_DESC"),A429_SIGNAL_FLOAT_DESC_obj->get_id());

              A429_SIGNAL_INT_DESC_obj->insert_intable_new(id);
              A429_SIGNAL_obj->set_reference(QString("A429_SIGNAL_INT_DESC"),A429_SIGNAL_INT_DESC_obj->get_id());

              A429_SIGNAL_OPAQUE_DESC_obj->insert_intable_new(id);
              A429_SIGNAL_obj->set_reference(QString("A429_SIGNAL_OPAQUE_DESC"),A429_SIGNAL_OPAQUE_DESC_obj->get_id());

              A429_SIGNAL_TYPE_obj->insert_intable_new(id);

              A429_SIGNAL_obj->set_reference(QString("A429_BUS"),A429_BUS_obj->get_id());
              A429_SIGNAL_obj->set_reference(QString("A429_LABEL"),A429_LABEL_obj->get_id());
              A429_SIGNAL_obj->set_reference(QString("A429_PARAMETER"),A429_PARAMETER_obj->get_id());
              A429_SIGNAL_obj->set_reference(QString("A429_SIGNAL_TYPE"),A429_SIGNAL_TYPE_obj->get_id());
           }
       }


       if(section==acicd_data_section::A429_INPUT_BUS)
       {
           A429_BUS_obj->modify_parameters({  { 2, "Name" },
                                { 3, "description" },
                                { 4, "EMC_protection" },
                                { 5, "Speed" },
                                { 6, "Parity_type" },
                                { 7, "transmission_rate" } });

           connector_pin_obj->modify_parameters({ { 8, "Connector_pin" } });

           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(connector_pin_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    connector_pin_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_BUS_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                    A429_BUS_obj->set_parameters(it_record-it->begin(),*it_record);
               }
           }

           connector_pin_obj->insert_intable_new(id);

           if(A429_BUS_obj->insert_intable_new(id))
           {
               A429_BUS_obj->set_reference(QString("EQUIPMENT"),equipment_obj->get_id());
               A429_BUS_obj->set_reference(QString("Connector_pin"),connector_pin_obj->get_id());
           }

       }

       if(section==acicd_data_section::A429_INPUT_LABEL)
       {
           A429_BUS_obj->modify_parameters({ { 5, "Name" } });
           A429_LABEL_obj->modify_parameters({ { 6, "Name" },
                                               { 7, "number" },
                                               { 10, "frequency" },
                                               { 11, "cycle_frequency" },
                                               { 12, "description" },
                                               { 13, "type" },
                                               { 14, "SDI" },
                                               { 15, "SDI_00" },
                                               { 16, "SDI_01" },
                                               { 17, "SDI_10" },
                                               { 18, "SDI_11" },
                                               { 19, "SSM_lenght" },
                                               { 20, "SSM_00" },
                                               { 21, "SSM_01" },
                                               { 22, "SSM_10" },
                                               { 23, "SSM_11" },
                                               { 26, "bit29_0" },
                                               { 27, "bit29_1" }   });

           A429_LABEL_TYPE_obj->modify_parameters({ { 13, "Name" } });

           A429_PARAMETER_obj->modify_parameters({  { 34, "Name" },
                                                 { 29, "local_name" },
                                                 { 30, "local_name_not_produced" },
                                                 { 31, "refresh_period" },
                                                 { 32, "fonctionnal_attribute" },
                                                 { 33, "name_description" },
                                                 { 36, "description" },
                                                 { 37, "ref_doc" } });

           A429_SIGNAL_obj->modify_parameters({  { 38, "Name" },
                                                 { 40, "description" },
                                                 { 41, "ref_doc" },
                                                 { 42, "nb_of_bit" },
                                                 { 43, "LSB" },
                                                 { 44, "MSB" },
                                                 { 45, "Transmit_order" },
                                                 { 46, "start_bit" } });

           A429_SIGNAL_TYPE_obj->modify_parameters({  { 39, "Name" }  });

           DATA_TYPE_obj->modify_parameters({  { 28, "Name" }  });

           KEYWORD_obj->modify_parameters({  { 35, "Name" } });


           A429_SIGNAL_BOOL_DESC_obj->modify_parameters({  { 47, "true_def" },
                                                           { 48, "false_def" },
                                                           { 49, "true_state" },
                                                           { 50, "false_state" },
                                                           { 51, "bool_logic" }});

           A429_SIGNAL_ENUMERATE_DESC_obj->modify_parameters({  { 54, "state" },
                                                                { 55, "value" } });

           A429_SIGNAL_FLOAT_DESC_obj->modify_parameters({  { 56, "min" },
                                                            { 57, "max" },
                                                            { 58, "unit" },
                                                            { 59, "accuracy" },
                                                            { 60, "coding_type" },
                                                            { 61, "resolution" },
                                                            { 62, "scale_factor" },
                                                            { 63, "offset" },
                                                            { 64, "signed" },
                                                            { 65, "non_linear_scale" } });

           A429_SIGNAL_INT_DESC_obj->modify_parameters({  { 66, "min" },
                                                          { 67, "max" },
                                                          { 68, "unit" },
                                                          { 69, "accuracy" },
                                                          { 70, "coding_type" },
                                                          { 71, "resolution" },
                                                          { 72, "scale_factor" },
                                                          { 73, "offset" },
                                                          { 74, "signed" },
                                                          { 75, "non_linear_scale" } });

           A429_SIGNAL_OPAQUE_DESC_obj->modify_parameters({   { 76, "size" },
                                                              { 77, "length" } });

           A429_SIGNAL_STRING_DESC_obj->modify_parameters({  { 52, "length" },
                                                             { 53, "format" } });

           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(APPLICATION_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        APPLICATION_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_BUS_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_BUS_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_LABEL_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_LABEL_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_LABEL_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_LABEL_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_PARAMETER_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_PARAMETER_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(DATA_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        DATA_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(KEYWORD_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        KEYWORD_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_BOOL_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_BOOL_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_ENUMERATE_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_ENUMERATE_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_FLOAT_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_FLOAT_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_INT_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_INT_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_OPAQUE_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_OPAQUE_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(A429_SIGNAL_STRING_DESC_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        A429_SIGNAL_STRING_DESC_obj->set_parameters(it_record-it->begin(),*it_record);
               }
           }

           A429_BUS_obj->insert_intable_new(id);
           if(A429_LABEL_obj->insert_intable_new(id))
           {


               APPLICATION_obj->insert_intable_new(id);
               A429_LABEL_TYPE_obj->insert_intable_new(id);

               A429_LABEL_obj->set_reference(QString("A429_BUS"),A429_BUS_obj->get_id());
               A429_LABEL_obj->set_reference(QString("APPLICATION"),APPLICATION_obj->get_id());
               A429_LABEL_obj->set_reference(QString("type"),A429_LABEL_TYPE_obj->get_id());
           }

           if(A429_PARAMETER_obj->insert_intable_new(id))
           {
               DATA_TYPE_obj->insert_intable_new(id);
               KEYWORD_obj->insert_intable_new(id);

               A429_PARAMETER_obj->set_reference(QString("A429_BUS"),A429_BUS_obj->get_id());
               A429_PARAMETER_obj->set_reference(QString("A429_LABEL"),A429_LABEL_obj->get_id());
               A429_PARAMETER_obj->set_reference(QString("type"),DATA_TYPE_obj->get_id());
               A429_PARAMETER_obj->set_reference(QString("keyword"),KEYWORD_obj->get_id());
           }

           if(A429_SIGNAL_obj->insert_intable_new(id))
           {

              A429_SIGNAL_BOOL_DESC_obj->insert_intable_new(id);
              A429_SIGNAL_obj->set_reference(QString("A429_SIGNAL_BOOL_DESC"),A429_SIGNAL_BOOL_DESC_obj->get_id());

              A429_SIGNAL_STRING_DESC_obj->insert_intable_new(id);
              A429_SIGNAL_obj->set_reference(QString("A429_SIGNAL_STRING_DESC"),A429_SIGNAL_STRING_DESC_obj->get_id());

              A429_SIGNAL_ENUMERATE_DESC_obj->insert_intable_new(id);
              A429_SIGNAL_obj->set_reference(QString("A429_SIGNAL_ENUMERATE_DESC"),A429_SIGNAL_ENUMERATE_DESC_obj->get_id());

              A429_SIGNAL_FLOAT_DESC_obj->insert_intable_new(id);
              A429_SIGNAL_obj->set_reference(QString("A429_SIGNAL_FLOAT_DESC"),A429_SIGNAL_FLOAT_DESC_obj->get_id());

              A429_SIGNAL_INT_DESC_obj->insert_intable_new(id);
              A429_SIGNAL_obj->set_reference(QString("A429_SIGNAL_INT_DESC"),A429_SIGNAL_INT_DESC_obj->get_id());

              A429_SIGNAL_OPAQUE_DESC_obj->insert_intable_new(id);
              A429_SIGNAL_obj->set_reference(QString("A429_SIGNAL_OPAQUE_DESC"),A429_SIGNAL_OPAQUE_DESC_obj->get_id());

              A429_SIGNAL_TYPE_obj->insert_intable_new(id);

              A429_SIGNAL_obj->set_reference(QString("A429_BUS"),A429_BUS_obj->get_id());
              A429_SIGNAL_obj->set_reference(QString("A429_LABEL"),A429_LABEL_obj->get_id());
              A429_SIGNAL_obj->set_reference(QString("A429_PARAMETER"),A429_PARAMETER_obj->get_id());
              A429_SIGNAL_obj->set_reference(QString("A429_SIGNAL_TYPE"),A429_SIGNAL_TYPE_obj->get_id());
           }

       }

       if(section==acicd_data_section::ANALOGUE_OUTPUT_LINE)
       {

           connector_pin_obj->modify_parameters({ { 5, "Connector_pin" } });

           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(connector_pin_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        connector_pin_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(ANA_LINE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        ANA_LINE_obj->set_parameters(it_record-it->begin(),*it_record);
               }
           }



           if(ANA_LINE_obj->insert_intable_new(id))
           {
               connector_pin_obj->insert_intable_new(id);
               ANA_LINE_obj->set_reference(QString("EQUIPMENT"),equipment_obj->get_id());
               ANA_LINE_obj->set_reference(QString("CONNECTOR_PIN"),connector_pin_obj->get_id());
           }
       }


       if(section==acicd_data_section::ANALOGUE_OUTPUT_SIGNAL)
       {

           ANA_LINE_obj->modify_parameters({ { 5, "Name" } });
           DATA_TYPE_obj->modify_parameters({ { 6, "Name" } });
           KEYWORD_obj->modify_parameters({ { 13, "Name" } });

           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(ANA_LINE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        ANA_LINE_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(ANA_PARAMETER_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        ANA_PARAMETER_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(ANA_SIGNAL_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        ANA_SIGNAL_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(DATA_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        DATA_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(KEYWORD_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        KEYWORD_obj->set_parameters(it_record-it->begin(),*it_record);
               }
           }

           ANA_LINE_obj->insert_intable_new(id);
           DATA_TYPE_obj->insert_intable_new(id);

           if(ANA_PARAMETER_obj->insert_intable_new(id))
           {
               KEYWORD_obj->insert_intable_new(id);
               ANA_PARAMETER_obj->set_reference(QString("ANA_LINE"),ANA_LINE_obj->get_id());
               ANA_PARAMETER_obj->set_reference(QString("keyword"),KEYWORD_obj->get_id());
               ANA_PARAMETER_obj->set_reference(QString("type"),DATA_TYPE_obj->get_id());
           }
           if(ANA_SIGNAL_obj->insert_intable_new(id))
           {
               ANA_SIGNAL_obj->set_reference(QString("ANA_PARAMETER"),ANA_PARAMETER_obj->get_id());
               ANA_SIGNAL_obj->set_reference(QString("ANA_LINE"),ANA_LINE_obj->get_id());
               ANA_SIGNAL_obj->set_reference(QString("type"),DATA_TYPE_obj->get_id());
           }
       }




       if(section==acicd_data_section::ANALOGUE_INPUT_LINE)
       {
           ANA_LINE_obj->modify_parameters({ { 2, "Name" },
                                             { 3, "description" },
                                             { 4, "EMC_protection" } });
           connector_pin_obj->modify_parameters({ { 5, "Connector_pin" } });

           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(connector_pin_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        connector_pin_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(ANA_LINE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        ANA_LINE_obj->set_parameters(it_record-it->begin(),*it_record);
               }
           }

           if(ANA_LINE_obj->insert_intable_new(id))
           {
               connector_pin_obj->insert_intable_new(id);
               ANA_LINE_obj->set_reference(QString("EQUIPMENT"),equipment_obj->get_id());
               ANA_LINE_obj->set_reference(QString("CONNECTOR_PIN"),connector_pin_obj->get_id());
           }
       }

       if(section==acicd_data_section::ANALOGUE_INPUT_SIGNAL)
       {

           ANA_LINE_obj->modify_parameters({ { 5, "Name" } });
           DATA_TYPE_obj->modify_parameters({ { 6, "Name" } });
           KEYWORD_obj->modify_parameters({ { 13, "Name" } });

           for(it_record=it->begin();it_record!=it->end();++it_record)
           {
               if(ANA_LINE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        ANA_LINE_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(ANA_PARAMETER_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        ANA_PARAMETER_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(ANA_SIGNAL_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        ANA_SIGNAL_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(DATA_TYPE_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        DATA_TYPE_obj->set_parameters(it_record-it->begin(),*it_record);
               }
               if(KEYWORD_obj->DB_FIELDS.count(it_record-it->begin())==1)
               {
                        KEYWORD_obj->set_parameters(it_record-it->begin(),*it_record);
               }
           }

           ANA_LINE_obj->insert_intable_new(id);
           DATA_TYPE_obj->insert_intable_new(id);

           if(ANA_PARAMETER_obj->insert_intable_new(id))
           {
               KEYWORD_obj->insert_intable_new(id);
               ANA_PARAMETER_obj->set_reference(QString("ANA_LINE"),ANA_LINE_obj->get_id());
               ANA_PARAMETER_obj->set_reference(QString("keyword"),KEYWORD_obj->get_id());
               ANA_PARAMETER_obj->set_reference(QString("type"),DATA_TYPE_obj->get_id());
           }
           if(ANA_SIGNAL_obj->insert_intable_new(id))
           {
               ANA_SIGNAL_obj->set_reference(QString("ANA_PARAMETER"),ANA_PARAMETER_obj->get_id());
               ANA_SIGNAL_obj->set_reference(QString("ANA_LINE"),ANA_LINE_obj->get_id());
               ANA_SIGNAL_obj->set_reference(QString("type"),DATA_TYPE_obj->get_id());
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
 //       Id=this->is_acicd_exist(DB_VALUES_ACICD["Name"]);

        // acicd is not in DB
//        if(Id==0)
//        {
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

            query.bindValue(":rowid", id);
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
 //               BDD->sql_log_file <<"set_equipment_reference: "
 //                                    << query.lastError().text()<<endl;
 //               qDebug() << "set_equipment_reference: "
  //                       << query.lastError();
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

        query.prepare("SELECT rowid, Name FROM ACICD WHERE Name = (:name)");
        query.bindValue(":name", Name);

        success=query.exec();

        if(!success)
        {
  //          qDebug() << "is_acicd_exist: "
  //                   << query.lastError();
        }
        else
        {
            // on first valid record
            query.first();

            // record is valid
            if(query.isValid())
            {
                // number of matching record = 0 => acicd is not in db
                if(query.value("rowid")==0)
                {
                    return 0;
                }

                // acicd is already in db
                else
                {
                    return query.value("rowid").toInt();
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
 //           BDD->sql_log_file <<"delete_acicd: "
 //                                << query.lastError().text()<<endl;
 //           qDebug() << "delete_acicd: "
 //                    << query.lastError();
        }
        else
        {
            db->commit();
        }

    }
    return success;
}
