#include "acicd_afdx_signal_bool_charact.h"

acicd_afdx_signal_bool_charact::acicd_afdx_signal_bool_charact(sql_database_manager *database_manager) : acicd_element (database_manager)
{
    DB_FIELDS= { { 41, "true_def" },
                 { 42, "false_def" },
                 { 43, "true_state" },
                 { 44, "false_state" },
                 { 45, "bool_logic" },
               };

    DB_table_name="AFDX_SIGNAL_BOOL_DESC";
    test_field="rowid";

    insert_query=QString("INSERT INTO %1 VALUES(NULL,:true_def,:false_def,:true_state,:false_state,:bool_logic)").arg(DB_table_name);
    test_query=QString("SELECT rowid, %1 FROM %2 WHERE %1 = (:test_field)").arg(test_field).arg(DB_table_name);

    create_table_query=QString("\
             CREATE TABLE IF NOT EXISTS [%1](\
                [true_def] VARCHAR( 45 ) NULL,\
                [false_def] VARCHAR( 45 ) NULL,\
                [true_state] VARCHAR( 45 ) NULL,\
                [false_state] VARCHAR( 45 ) NULL,\
                [bool_logic] VARCHAR( 45 ) NULL,\
                PRIMARY KEY(true_def,false_def,true_state,false_state,bool_logic)\
                );\n\
            ").arg(DB_table_name);

    database_manager->create_table(create_table_query);
}

bool acicd_afdx_signal_bool_charact::test_intable(void)
{
//d    int Id = -1;
    bool success = false;

    if (db->isOpen())
    {

            QSqlQuery query(*db);
            std::map<QString,QString>::iterator iterator;

            query.prepare(insert_query);

            for(iterator=(this->DB_VALUES).begin();iterator!=(this->DB_VALUES.end());++iterator)
            {
                 query.bindValue(":"+iterator->first, iterator->second);
            }
            BDD->sql_log_file << "[test_intable] [" + insert_query + "] test_intable"  <<endl;
            success = query.exec();

            // Get database given autoincrement value
            if (success)
            {
                // http://www.sqlite.org/c3ref/last_insert_rowid.html
                id = query.lastInsertId().toInt();
                //Element_collection[this->get_value(test_field).toStdString()]=Id;
               // id=Id;
                return true;
            }
            else
            {
                BDD->sql_log_file <<"test_intable: "
                                    << query.lastError().text() <<endl;
                qDebug() << "test_intable: "
                         << query.lastError();
                return false;
            }
    }
    else
    {
        return false;
    }

}
