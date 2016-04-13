#include "acicd_afdx_tx_port.h"

acicd_AFDX_TX_port::acicd_AFDX_TX_port(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 10, "Network_Select" },
                 { 15, "TX_AFDX_port_Identifier" },
                 { 16, "AFDX_Port_Master_Name" },
                 { 19, "IP_frag_allowed" },
                 { 21, "Src_IP_Adress" },
                 { 22, "Dest_IP_Adress" },
                 { 23, "Src_UDP_Adress" },
                 { 24, "Dest_UDP_Adress" },
                 { 25, "Buffersize" }
               };

    DB_table_name="AFDX_TX_PORT";
    test_field="TX_AFDX_port_Identifier";

    insert_query=QString("INSERT INTO %1 VALUES(NULL,:TX_AFDX_port_Identifier,:AFDX_Port_Master_Name,NULL,NULL,NULL,NULL,:Src_IP_Adress,:Dest_IP_Adress,:Src_UDP_Adress,:Dest_UDP_Adress,:Buffersize,:IP_frag_allowed,:ACICD,:AFDX_VL,:Network_Select)").arg(DB_table_name);
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query=QString("CREATE TABLE IF NOT EXISTS [%1](\
             [id] INTEGER CONSTRAINT [pk_%1] NOT NULL PRIMARY KEY AUTOINCREMENT,\
             [TX_AFDX_port_Identifier] INTEGER NULL,\
             [AFDX_Port_Master_Name] VARCHAR( 45 ) NULL,\
             [Type] INTEGER NULL,\
             [characteristic] INTEGER NULL,\
             [transmission_type] INTEGER NULL,\
             [EQUIPMENT] INTEGER NULL,\
             [Src_IP_Adress] VARCHAR( 15 ) NULL,\
             [Dest_IP_Adress] VARCHAR( 15 ) NULL,\
             [Src_UDP_Adress] INTEGER NULL,\
             [Dest_UDP_Adress] INTEGER NULL,\
             [Buffersize] INTEGER NULL,\
             [IP_frag_allowed] BIT NULL,\
             [ACICD] INTEGER NULL,\
             [AFDX_VL] INTEGER NULL,\
             [Network_Select] VARCHAR( 15 ) NULL,\
                CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [id] ),\
                CONSTRAINT [Type]\
                    FOREIGN KEY([Type])\
                    REFERENCES [AFDX_PORT_TYPE] ( [id] ),\
                CONSTRAINT [characteristic]\
                    FOREIGN KEY([characteristic])\
                    REFERENCES [AFDX_PORT_CHARACTERISTIC] ( [id] ),\
                CONSTRAINT [transmission_type]\
                    FOREIGN KEY([transmission_type])\
                    REFERENCES [AFDX_PORT_TRANSMISSION_TYPE] ( [id] ),\
                CONSTRAINT [AFDX_VL]\
                    FOREIGN KEY([AFDX_VL])\
                    REFERENCES [AFDX_VL] ( [id] ),\
                CONSTRAINT [EQUIPMENT]\
                    FOREIGN KEY([EQUIPMENT])\
                    REFERENCES [EQUIPMENT] ( [id] )\
            );\n\
            ").arg(DB_table_name);

     database_manager->create_table(create_table_query);
}
