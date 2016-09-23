#include "micd_port_in.h"

micd_port_in::micd_port_in(sql_database_manager *database_manager) : micd_element (database_manager)
{
    DB_FIELDS= { { 0, "Name" },
                 { 1, "Type" },
                 { 2, "Unit" },
                 { 3, "Description" },
                 { 4, "Convention" },
                 { 5, "Dim1" },
                 { 6, "Dim2" },
                 { 7, "Com_format" },
                 { 8, "Com_mode" },
                 { 9, "From" },
                 { 10, "Refresh_rate" },
                 { 11, "Min" },
                 { 12, "Max" },
                 { 13, "Enum" },
                 { 14, "Consumed_if" },
                 { 15, "Aircraft_signal_name" }
               };

    DB_table_name="PORTS_IN";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:MICD,:Name,:Type,:Unit,:Description,:Convention,:Dim1,:Dim2,:Com_format,:Com_mode,:From,:Refresh_rate,:Min,:Max,:Enum,:Consumed_if,:Aircraft_signal_name,:Interface_level,:Status,:Simulation_level,:Init_value,:Custom,:Comment,:Last_modification)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name) AND (Type=:Type);").arg(DB_table_name);

    create_table_query=QString("\
       CREATE TABLE IF NOT EXISTS [%1](\
        [MICD] INTEGER NULL,\
        [Name] TEXT CHECK (Name != ''),\
        [Type] TEXT CHECK (Type != ''),\
        [Unit] TEXT,\
        [Description] TEXT,\
        [Convention] TEXT,\
        [Dim1] INTEGER,\
        [Dim2] INTEGER,\
        [Com_format] TEXT,\
        [Com_mode] TEXT ,\
        [From] TEXT,\
        [Refresh_rate] TEXT,\
        [Min] REAL,\
        [Max] REAL,\
        [Enum] TEXT,\
        [Consumed_if] TEXT,\
        [Aircraft_signal_name] TEXT,\   
        [Interface_level] TEXT,\
        [Status] INTEGER,\
        [Simulation_level] TEXT,\
        [Init_value] REAL,\
        [Custom] TEXT,\
        [Comment] TEXT,\
        [Last_modification] TEXT,\
        CONSTRAINT [MICD] \
                   FOREIGN KEY([MICD]) \
                   REFERENCES [MICD] ( [rowid] ), \
        CONSTRAINT unique_combinaison PRIMARY KEY (Name,Type) ON CONFLICT IGNORE\
       );\n\
       ").arg(DB_table_name);

     database_manager->create_table(create_table_query);
}
