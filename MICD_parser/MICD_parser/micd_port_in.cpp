#include "micd_port_in.h"

micd_port_in::micd_port_in(sql_database_manager *database_manager) : micd_element (database_manager)
{
    DB_FIELDS= { { 5, "Dim1" },
                 { 6, "Dim2" },
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
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name);").arg(DB_table_name);

    create_table_query=QString("\
       CREATE TABLE IF NOT EXISTS [%1](\
        [MICD] INTEGER NULL,\
        [Name] INTEGER CHECK (Name != ''),\
        [Type] INTEGER CHECK (Type != ''),\
        [Unit] INTEGER,\
        [Description] INTEGER,\
        [Convention] INTEGER,\
        [Dim1] INTEGER,\
        [Dim2] INTEGER,\
        [Com_format] INTEGER,\
        [Com_mode] INTEGER ,\
        [From] INTEGER,\
        [Refresh_rate] TEXT,\
        [Min] REAL,\
        [Max] REAL,\
        [Enum] INTEGER,\
        [Consumed_if] INTEGER,\
        [Aircraft_signal_name] INTEGER,\
        [Interface_level] INTEGER,\
        [Status] INTEGER,\
        [Simulation_level] TEXT,\
        [Init_value] REAL,\
        [Custom] TEXT,\
        [Comment] TEXT,\
        [Last_modification] TEXT,\
                CONSTRAINT [Description] \
                            FOREIGN KEY([Description]) \
                            REFERENCES [DESCRIPTIONS] ( [rowid] ), \
                CONSTRAINT [Convention] \
                            FOREIGN KEY([Convention]) \
                            REFERENCES [CONVENTION] ( [rowid] ), \
                CONSTRAINT [Com_format] \
                            FOREIGN KEY([Com_format]) \
                            REFERENCES [COM_FORMAT] ( [rowid] ), \
                CONSTRAINT [Com_mode] \
                            FOREIGN KEY([Com_mode]) \
                            REFERENCES [COM_MODE] ( [rowid] ), \
                CONSTRAINT [From] \
                            FOREIGN KEY([From]) \
                            REFERENCES [FROM_TO] ( [rowid] ), \
                CONSTRAINT [Enum] \
                            FOREIGN KEY([Enum]) \
                            REFERENCES [ENUM] ( [rowid] ), \
                CONSTRAINT [Consumed_if] \
                            FOREIGN KEY([Consumed_if]) \
                            REFERENCES [CONS_PROD_IF] ( [rowid] ), \
                CONSTRAINT [Aircraft_signal_name] \
                            FOREIGN KEY([Aircraft_signal_name]) \
                            REFERENCES [AIRCRAFT_SIGNAL_NAME] ( [rowid] ), \
                CONSTRAINT [Interface_level] \
                            FOREIGN KEY([Interface_level]) \
                            REFERENCES [INTERFACE_LEVEL] ( [rowid] ), \
                CONSTRAINT [Unit] \
                    FOREIGN KEY([Unit]) \
                    REFERENCES [UNITS] ( [rowid] ), \
        CONSTRAINT [Name] \
                   FOREIGN KEY([Name]) \
                   REFERENCES [PORTS_NAME] ( [rowid] ), \
        CONSTRAINT [Type] \
                   FOREIGN KEY([Type]) \
                   REFERENCES [DATA_TYPE] ( [rowid] ), \
        CONSTRAINT [MICD] \
                   FOREIGN KEY([MICD]) \
                   REFERENCES [MICD] ( [rowid] ), \
        CONSTRAINT unique_combinaison PRIMARY KEY (Name) ON CONFLICT IGNORE\
       );\n\
       ").arg(DB_table_name);

     database_manager->create_table(create_table_query);
}
