#include "acicd_a429_signal.h"

acicd_a429_signal::acicd_a429_signal(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 37, "Name" },
                 { 39, "description" },
                 { 40, "ref_doc" },
                 { 41, "nb_of_bit" },
                 { 42, "LSB" },
                 { 43, "MSB" },
                 { 44, "Transmit_order" },
                 { 45, "start_bit" }
               };

    DB_table_name="A429_SIGNAL";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name,:description,:ref_doc,:nb_of_bit,:LSB,:MSB,:Transmit_order,:start_bit,:A429_SIGNAL_TYPE,:A429_SIGNAL_BOOL_DESC,:A429_SIGNAL_STRING_DESC,:A429_SIGNAL_ENUMERATE_DESC,:A429_SIGNAL_FLOAT_DESC,:A429_SIGNAL_INT_DESC,:A429_SIGNAL_OPAQUE_DESC,:A429_LABEL,:A429_BUS,:A429_PARAMETER,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [Name] VARCHAR( 45 ) NULL, \
                [description] VARCHAR( 45 ) NULL, \
                [ref_doc] VARCHAR( 45 ) NULL, \
                [nb_of_bit] INTEGER NULL, \
                [LSB] INTEGER NULL, \
                [MSB] INTEGER NULL, \
                [Transmit_order] INTEGER NULL, \
                [start_bit] INTEGER NULL, \
                [A429_SIGNAL_TYPE] INTEGER NULL, \
                [A429_SIGNAL_BOOL_DESC] INTEGER NULL, \
                [A429_SIGNAL_STRING_DESC] INTEGER NULL, \
                [A429_SIGNAL_ENUMERATE_DESC] INTEGER NULL, \
                [A429_SIGNAL_FLOAT_DESC] INTEGER NULL, \
                [A429_SIGNAL_INT_DESC] INTEGER NULL, \
                [A429_SIGNAL_OPAQUE_DESC] INTEGER NULL, \
                [A429_LABEL] INTEGER NULL, \
                [A429_BUS] INTEGER NULL, \
                [A429_PARAMETER] INTEGER NULL, \
                [ACICD] INTEGER NULL, \
                 CONSTRAINT unique_combinaison PRIMARY KEY (Name,ACICD) ON CONFLICT IGNORE,\
                 CONSTRAINT [ACICD]\
                        FOREIGN KEY([ACICD])\
                        REFERENCES [ACICD] ( [rowid] ),\
                 CONSTRAINT [A429_SIGNAL_TYPE] \
                        FOREIGN KEY([A429_SIGNAL_TYPE]) \
                        REFERENCES [A429_SIGNAL_TYPE] ( [rowid] ), \
                 CONSTRAINT [A429_SIGNAL_BOOL_DESC] \
                        FOREIGN KEY([A429_SIGNAL_BOOL_DESC]) \
                        REFERENCES [A429_SIGNAL_BOOL_DESC] ( [rowid] ), \
                 CONSTRAINT [A429_SIGNAL_STRING_DESC] \
                        FOREIGN KEY([A429_SIGNAL_STRING_DESC]) \
                        REFERENCES [A429_SIGNAL_STRING_DESC] ( [rowid] ), \
                 CONSTRAINT [A429_SIGNAL_ENUMERATE_DESC] \
                        FOREIGN KEY([A429_SIGNAL_ENUMERATE_DESC]) \
                        REFERENCES [A429_SIGNAL_ENUMERATE_DESC] ( [rowid] ), \
                 CONSTRAINT [A429_SIGNAL_INT_DESC] \
                        FOREIGN KEY([A429_SIGNAL_INT_DESC]) \
                        REFERENCES [A429_SIGNAL_INT_DESC] ( [rowid] ), \
                 CONSTRAINT [A429_SIGNAL_OPAQUE_DESC] \
                        FOREIGN KEY([A429_SIGNAL_OPAQUE_DESC]) \
                        REFERENCES [A429_SIGNAL_OPAQUE_DESC] ( [rowid] ), \
                 CONSTRAINT [A429_SIGNAL_FLOAT_DESC] \
                        FOREIGN KEY([A429_SIGNAL_FLOAT_DESC]) \
                        REFERENCES [A429_SIGNAL_FLOAT_DESC] ( [rowid] ), \
                 CONSTRAINT [A429_LABEL] \
                        FOREIGN KEY([A429_LABEL]) \
                        REFERENCES [A429_LABEL] ( [rowid] ), \
                 CONSTRAINT [A429_BUS] \
                        FOREIGN KEY([A429_BUS]) \
                        REFERENCES [A429_BUS] ( [rowid] ), \
                CONSTRAINT [A429_PARAMETER] \
                        FOREIGN KEY([A429_PARAMETER]) \
                        REFERENCES [A429_PARAMETER] ( [rowid] ) \
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
