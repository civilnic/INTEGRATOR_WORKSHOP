#include "acicd_afdx_signal.h"

acicd_afdx_signal::acicd_afdx_signal(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 34, "Name" },
                 { 36, "description" },
                 { 37, "ref_doc" },
                 { 38, "nb_of_bit" },
                 { 39, "address" },
                 { 40, "position" },
               };

    DB_table_name="AFDX_SIGNAL";
    test_field="Name";

    insert_query=QString("INSERT INTO %1 VALUES(:Name,:description,:ref_doc,:nb_of_bit,:address,:position,:AFDX_SIGNAL_TYPE,:AFDX_SIGNAL_BOOL_DESC,:AFDX_SIGNAL_STRING_DESC,:AFDX_SIGNAL_ENUMERATE_DESC,:AFDX_SIGNAL_FLOAT_DESC,:AFDX_SIGNAL_INT_DESC,:AFDX_SIGNAL_OPAQUE_DESC,:AFDX_MESSAGE,:AFDX_FDS,:AFDX_FS,:AFDX_VL,:AFDX_PARAMETER,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT rowid FROM %1 WHERE (Name=:Name) AND (ACICD=:ACICD);").arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [Name] VARCHAR( 45 ) NULL, \
                [description] VARCHAR( 45 ) NULL, \
                [ref_doc] VARCHAR( 45 ) NULL, \
                [nb_of_bit] INTEGER NULL, \
                [address] VARCHAR( 45 ) NULL, \
                [position] INTEGER NULL, \
                [AFDX_SIGNAL_TYPE] INTEGER NULL, \
                [AFDX_SIGNAL_BOOL_DESC] INTEGER NULL, \
                [AFDX_SIGNAL_STRING_DESC] INTEGER NULL, \
                [AFDX_SIGNAL_ENUMERATE_DESC] INTEGER NULL, \
                [AFDX_SIGNAL_FLOAT_DESC] INTEGER NULL, \
                [AFDX_SIGNAL_INT_DESC] INTEGER NULL, \
                [AFDX_SIGNAL_OPAQUE_DESC] INTEGER NULL, \
                [AFDX_MESSAGE] INTEGER NULL, \
                [AFDX_FDS] INTEGER NULL, \
                [AFDX_FS] INTEGER NULL, \
                [AFDX_VL] INTEGER NULL, \
                [AFDX_PARAMETER] INTEGER NULL, \
                [ACICD] INTEGER NULL, \
                 CONSTRAINT unique_combinaison PRIMARY KEY (Name,ACICD) ON CONFLICT IGNORE,\
                 CONSTRAINT [ACICD]\
                        FOREIGN KEY([ACICD])\
                        REFERENCES [ACICD] ( [rowid] ),\
                 CONSTRAINT [AFDX_SIGNAL_TYPE] \
                        FOREIGN KEY([AFDX_SIGNAL_TYPE]) \
                        REFERENCES [AFDX_SIGNAL_TYPE] ( [rowid] ), \
                 CONSTRAINT [AFDX_SIGNAL_BOOL_DESC] \
                        FOREIGN KEY([AFDX_SIGNAL_BOOL_DESC]) \
                        REFERENCES [AFDX_SIGNAL_BOOL_DESC] ( [rowid] ), \
                 CONSTRAINT [AFDX_SIGNAL_STRING_DESC] \
                        FOREIGN KEY([AFDX_SIGNAL_STRING_DESC]) \
                        REFERENCES [AFDX_SIGNAL_STRING_DESC] ( [rowid] ), \
                 CONSTRAINT [AFDX_SIGNAL_ENUMERATE_DESC] \
                        FOREIGN KEY([AFDX_SIGNAL_ENUMERATE_DESC]) \
                        REFERENCES [AFDX_SIGNAL_ENUMERATE_DESC] ( [rowid] ), \
                 CONSTRAINT [AFDX_SIGNAL_INT_DESC] \
                        FOREIGN KEY([AFDX_SIGNAL_INT_DESC]) \
                        REFERENCES [AFDX_SIGNAL_INT_DESC] ( [rowid] ), \
                 CONSTRAINT [AFDX_SIGNAL_OPAQUE_DESC] \
                        FOREIGN KEY([AFDX_SIGNAL_OPAQUE_DESC]) \
                        REFERENCES [AFDX_SIGNAL_OPAQUE_DESC] ( [rowid] ), \
                 CONSTRAINT [AFDX_SIGNAL_FLOAT_DESC] \
                        FOREIGN KEY([AFDX_SIGNAL_FLOAT_DESC]) \
                        REFERENCES [AFDX_SIGNAL_FLOAT_DESC] ( [rowid] ), \
                 CONSTRAINT [AFDX_MESSAGE] \
                        FOREIGN KEY([AFDX_MESSAGE]) \
                        REFERENCES [AFDX_MESSAGE] ( [rowid] ), \
                 CONSTRAINT [AFDX_FDS] \
                        FOREIGN KEY([AFDX_FDS]) \
                        REFERENCES [AFDX_FDS] ( [rowid] ), \
                 CONSTRAINT [AFDX_VL] \
                        FOREIGN KEY([AFDX_VL]) \
                        REFERENCES [AFDX_VL] ( [rowid] ), \
                CONSTRAINT [AFDX_PARAMETER] \
                        FOREIGN KEY([AFDX_PARAMETER]) \
                        REFERENCES [AFDX_PARAMETER] ( [rowid] ), \
                 CONSTRAINT [AFDX_FS] \
                        FOREIGN KEY([AFDX_FS]) \
                        REFERENCES [AFDX_FS] ( [rowid] ) \
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
