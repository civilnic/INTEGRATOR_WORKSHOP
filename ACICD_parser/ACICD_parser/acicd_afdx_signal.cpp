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

    insert_query=QString("INSERT INTO %1 VALUES(NULL,:Name,:description,:ref_doc,:nb_of_bit,:address,:position,:AFDX_SIGNAL_TYPE,:AFDX_SIGNAL_BOOL_DESC,:AFDX_SIGNAL_STRING_DESC,:AFDX_SIGNAL_ENUMERATE_DESC,:AFDX_SIGNAL_FLOAT_DESC,:AFDX_SIGNAL_INT_DESC,:AFDX_SIGNAL_OPAQUE_DESC,:AFDX_MESSAGE,:AFDX_SIGNAL_OPAQUE_DESC,:AFDX_FDS,:AFDX_FS,:ACICD)").arg(DB_table_name);
    test_query=QString("SELECT id, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [id] INTEGER CONSTRAINT [pk_%1] NOT NULL PRIMARY KEY  AUTOINCREMENT,  \
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
                [ACICD] INTEGER NULL, \
                 CONSTRAINT [ACICD]\
                        FOREIGN KEY([ACICD])\
                        REFERENCES [ACICD] ( [id] ),\
                 CONSTRAINT [AFDX_SIGNAL_TYPE] \
                        FOREIGN KEY([AFDX_SIGNAL_TYPE]) \
                        REFERENCES [AFDX_SIGNAL_TYPE] ( [id] ), \
                 CONSTRAINT [AFDX_SIGNAL_BOOL_DESC] \
                        FOREIGN KEY([AFDX_SIGNAL_BOOL_DESC]) \
                        REFERENCES [AFDX_SIGNAL_BOOL_DESC] ( [id] ), \
                 CONSTRAINT [AFDX_SIGNAL_STRING_DESC] \
                        FOREIGN KEY([AFDX_SIGNAL_STRING_DESC]) \
                        REFERENCES [AFDX_SIGNAL_STRING_DESC] ( [id] ), \
                 CONSTRAINT [AFDX_SIGNAL_ENUMERATE_DESC] \
                        FOREIGN KEY([AFDX_SIGNAL_ENUMERATE_DESC]) \
                        REFERENCES [AFDX_SIGNAL_ENUMERATE_DESC] ( [id] ), \
                 CONSTRAINT [AFDX_SIGNAL_INT_DESC] \
                        FOREIGN KEY([AFDX_SIGNAL_INT_DESC]) \
                        REFERENCES [AFDX_SIGNAL_INT_DESC] ( [id] ), \
                 CONSTRAINT [AFDX_SIGNAL_OPAQUE_DESC] \
                        FOREIGN KEY([AFDX_SIGNAL_OPAQUE_DESC]) \
                        REFERENCES [AFDX_SIGNAL_OPAQUE_DESC] ( [id] ), \
                 CONSTRAINT [AFDX_SIGNAL_FLOAT_DESC] \
                        FOREIGN KEY([AFDX_SIGNAL_FLOAT_DESC]) \
                        REFERENCES [AFDX_SIGNAL_FLOAT_DESC] ( [id] ), \
                 CONSTRAINT [AFDX_MESSAGE] \
                        FOREIGN KEY([AFDX_MESSAGE]) \
                        REFERENCES [AFDX_MESSAGE] ( [id] ), \
                 CONSTRAINT [AFDX_FDS] \
                        FOREIGN KEY([AFDX_FDS]) \
                        REFERENCES [AFDX_FDS] ( [id] ), \
                 CONSTRAINT [AFDX_FS] \
                        FOREIGN KEY([AFDX_FS]) \
                        REFERENCES [AFDX_FS] ( [id] ) \
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}
