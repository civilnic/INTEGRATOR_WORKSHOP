#include "micd_port_in.h"

micd_port_in::micd_port_in(sql_database_manager *database_manager) : micd_element (database_manager)
{
    DB_FIELDS= { { 1, "Name" },
                 { 2, "Name" }
               };

    DB_table_name="UNITS";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name);").arg(DB_table_name);

    create_table_query=QString("\
       CREATE TABLE IF NOT EXISTS [%1](\
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
        [Status] INTEGER( 1 ),\
        [Simulation_level] TEXT,\
        [Init_value] REAL,\
        [Custom] TEXT,\
        [Comment] TEXT,\
        [Last_modification] TEXT\
        CONSTRAINT unique_combinaison PRIMARY KEY (Name) ON CONFLICT IGNORE\
       );\n\
       ").arg(DB_table_name);

     database_manager->create_table(create_table_query);
}
