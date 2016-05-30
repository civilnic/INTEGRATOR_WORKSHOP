#include "acicd_afdx_rx_port.h"

acicd_afdx_rx_port::acicd_afdx_rx_port(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 10, "Network_Select" },
                 { 16, "RX_AFDX_port_Identifier" },
                 { 17, "AFDX_Port_Master_Name" },
                 { 20, "IP_frag_allowed" },
                 { 21, "Dest_IP_Adress" },
                 { 22, "Dest_UDP_Adress" },
                 { 23, "Buffersize" }
               };

    DB_table_name="AFDX_RX_PORT";
    test_field="RX_AFDX_port_Identifier";

    insert_query=QString("INSERT INTO %1 VALUES(:RX_AFDX_port_Identifier,:AFDX_Port_Master_Name,NULL,NULL,NULL,NULL,:Dest_IP_Adress,:Dest_UDP_Adress,:Buffersize,:IP_frag_allowed,:ACICD,:AFDX_VL,:Network_Select)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (RX_AFDX_port_Identifier=:RX_AFDX_port_Identifier) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query=QString("CREATE TABLE IF NOT EXISTS [%1](\
             [RX_AFDX_port_Identifier] INTEGER NOT NULL,\
             [AFDX_Port_Master_Name] VARCHAR( 45 ) NULL,\
             [Type] INTEGER NULL,\
             [characteristic] INTEGER NULL,\
             [transmission_type] INTEGER NULL,\
             [EQUIPMENT] INTEGER NULL,\
             [Dest_IP_Adress] VARCHAR( 15 ) NULL,\
             [Dest_UDP_Adress] INTEGER NULL,\
             [Buffersize] INTEGER NULL,\
             [IP_frag_allowed] BIT NULL,\
             [ACICD] INTEGER NULL,\
             [AFDX_VL] INTEGER NULL,\
             [Network_Select] VARCHAR( 15 ) NULL,\
                CONSTRAINT unique_combinaison PRIMARY KEY (RX_AFDX_port_Identifier,ACICD) ON CONFLICT IGNORE,\
                CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [rowid] ),\
                CONSTRAINT [Type]\
                    FOREIGN KEY([Type])\
                    REFERENCES [AFDX_PORT_TYPE] ( [rowid] ),\
                CONSTRAINT [characteristic]\
                    FOREIGN KEY([characteristic])\
                    REFERENCES [AFDX_PORT_CHARACTERISTIC] ( [rowid] ),\
                CONSTRAINT [transmission_type]\
                    FOREIGN KEY([transmission_type])\
                    REFERENCES [AFDX_PORT_TRANSMISSION_TYPE] ( [rowid] ),\
                CONSTRAINT [AFDX_VL]\
                    FOREIGN KEY([AFDX_VL])\
                    REFERENCES [AFDX_VL] ( [rowid] ),\
                CONSTRAINT [EQUIPMENT]\
                    FOREIGN KEY([EQUIPMENT])\
                    REFERENCES [EQUIPMENT] ( [rowid] )\
            );\n\
            ").arg(DB_table_name);

     database_manager->create_table(create_table_query);
}
