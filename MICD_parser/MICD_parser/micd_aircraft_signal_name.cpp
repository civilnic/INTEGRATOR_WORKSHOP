#include "micd_aircraft_signal_name.h"

micd_aircraft_signal_name::micd_aircraft_signal_name(sql_database_manager *database_manager) : micd_simple_tab (database_manager)
{
    DB_FIELDS= { { 15, "Name" }
               };

    DB_table_name="AIRCRAFT_SIGNAL_NAME";


    this->init_table(database_manager);
}
