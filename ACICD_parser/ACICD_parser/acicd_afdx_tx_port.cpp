#include "acicd_afdx_tx_port.h"

acicd_AFDX_TX_port::acicd_AFDX_TX_port(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    id=-1;
    BDD=database_manager;
    db=(*BDD).get_db();

    DB_FIELDS= { { 15, "TX_AFDX_port_Identifier" },
                 { 16, "AFDX_Port_Master_Name" }
               };

    DB_table_name="AFDX_TX_PORT";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(NULL,:Name)").arg(DB_table_name);
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query=QString("CREATE TABLE IF NOT EXISTS [%1](\
             [id] INTEGER CONSTRAINT [pk_%1] NOT NULL PRIMARY KEY AUTOINCREMENT,\
             [Identifier] INTEGER NULL,\
             [Master_Name] VARCHAR( 45 ) NULL,\
             [Type] INTEGER NULL,\
             [characteristic] INTEGER NULL,\
             [transmission_type] INTEGER NULL,\
             [EQUIPMENT] INTEGER NOT NULL,\
             [Src_IP_Adress] VARCHAR( 15 ) NULL,\
             [Dest_IP_Adress] VARCHAR( 15 ) NULL,\
             [Src_UDP_Adress] INTEGER NULL,\
             [Dest_UDP_Adress] INTEGER NULL,\
             [Buffersize] INTEGER NULL,\
             [IP_frag_allowed] BIT NULL,\
             [ACICD] INTEGER NULL,\
                CONSTRAINT [ACICD]\
                    FOREIGN KEY([ACICD])\
                    REFERENCES [ACICD] ( [id] )\
                CONSTRAINT [Type]\
                    FOREIGN KEY([Type])\
                    REFERENCES [AFDX_port_type] ( [id] ),\
                CONSTRAINT [characteristic]\
                    FOREIGN KEY([characteristic])\
                    REFERENCES [AFDX_port_characteristic] (  ),\
                CONSTRAINT [transmission_type]\
                    FOREIGN KEY([transmission_type])\
                    REFERENCES [AFDX_port_transmission_type] ( [id] ),\
                CONSTRAINT [fk_AFDX_TX_port_EQUIPMENT1]\
                    FOREIGN KEY([EQUIPMENT])\
                    REFERENCES [EQUIPMENT] ( [id] )\
            );;\n\
            ").arg(DB_table_name);

     database_manager->create_table(create_table_query);
}
