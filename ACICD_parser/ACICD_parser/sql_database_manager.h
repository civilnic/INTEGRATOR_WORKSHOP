#ifndef SQL_DATABASE_H
#define SQL_DATABASE_H

#include <iostream>
#include <QSqlDatabase>
#include <QtSql>

#include "acicd_equipment.h"

class sql_database_manager
{
public:
    sql_database_manager(void);
    QSqlDatabase create_database(void);
    void open_database();
    void set_dbname(std::string name);
    bool create_acicd_table(void);
    bool create_equipment_table(void);
    int insert_acicd(QString Name, QString Path, int Micd, int Equipment, QString Version);
    int insert_equipment(acicd_equipment *equipment);
    int is_acicd_exist(QString Name);
    int is_equipment_exist(QString Name);
    bool delete_acicd(int id);
    std::string get_dbname(void);
    QSqlDatabase *get_db(void);

private:
    QSqlDatabase database;
    QString driver_type="QSQLITE";
    QString db_name="INTEGRATOR_WORKSHOP.db";
    QString db_user="root";
    QString db_pass="";
    QString db_hostname="localhost";

    const QString DB_QUERY_CREATE_ACICD="CREATE TABLE IF NOT EXISTS [ACICD](\
     [id] INTEGER CONSTRAINT [pk_ACICD] NOT NULL PRIMARY KEY AUTOINCREMENT,\
     [Name] VARCHAR( 45 ) NOT NULL,\
     [Path] VARCHAR( 45 ) NULL,\
     [Micd] INTEGER NULL,\
     [Equipment] INTEGER NULL,\
     [Version] VARCHAR( 5 ) NULL,\
      CONSTRAINT [Equipment]\
      FOREIGN KEY([Equipment])\
        REFERENCES [EQUIPMENT] ( [id] ));\n";

    const QString DB_QUERY_CREATE_CONNECTOR="CREATE TABLE IF NOT EXISTS [CONNECTOR]([id] INTEGER CONSTRAINT [pk_CONNECTOR] PRIMARY KEY  NOT NULL AUTOINCREMENT,[Equipment] INTEGER NULL,[ACICD] INTEGER NULL,\n\
    [Type] VARCHAR( 45 ) NULL,\n\
    [Name] VARCHAR( 45 ) NULL,\n\
    [Pin] VARCHAR( 45 ) NULL,\n\
    [Pin_Role] INTEGER NULL,\n\
    [Connection_Name] INTEGER NULL,\n\
    [Line_Type] INTEGER NULL,\n\
    [Speed] INTEGER NULL,\n\
    [NetworkId] VARCHAR( 3 ) NULL,\n\
    CONSTRAINT [Equipment]\n\
    FOREIGN KEY([Equipment])\n\
    REFERENCES [EQUIPMENT] ( [id] ),\n\
    CONSTRAINT [ACICD]\n\
    FOREIGN KEY([ACICD])\n\
    REFERENCES [ACICD] ( [id] ),\n\
    CONSTRAINT [Pin_Role]\n\
    FOREIGN KEY([Pin_Role])\n\
    REFERENCES [Connector_Pin_Role] ( [id] ),\n\
    CONSTRAINT [Line_Type]\n\
    FOREIGN KEY([Line_Type])\n\
    REFERENCES [Connector_Line_type] ( [id] ),\n\
    CONSTRAINT [Connection_Name]\n\
    FOREIGN KEY([Connection_Name])\n\
    REFERENCES [Connection_Name] ( [id] )\n\
    );\n";


    const QString DB_QUERY_CREATE_Connector_Line_type="\
            CREATE TABLE IF NOT EXISTS [Connector_Line_type](\
             [id] INTEGER CONSTRAINT [pk_Connector_Line_type] NOT NULL PRIMARY KEY  AUTOINCREMENT,  \
             [Name] VARCHAR( 45 ) NULL\
            );\n\
     ";

    const QString DB_QUERY_CREATE_Connector_Pin_Role="\
            CREATE TABLE IF NOT EXISTS [Connector_Pin_Role](\
             [id] INTEGER CONSTRAINT [pk_Connector_Pin_Role] NOT NULL PRIMARY KEY AUTOINCREMENT,\
             [Name] VARCHAR( 45 ) NULL\
            );\n\
     ";

    const QString DB_QUERY_CREATE_Connection_Name="\
            CREATE TABLE IF NOT EXISTS [Connection_Name](\
             [id] INTEGER CONSTRAINT [pk_Connection_Name ]NOT NULL PRIMARY KEY AUTOINCREMENT,\
             [Name] VARCHAR( 45 ) NULL\
            );\n\
     ";


    const QString DB_QUERY_CREATE_EQUIPMENT="\
        CREATE TABLE IF NOT EXISTS [EQUIPMENT](      \
         [id] INTEGER CONSTRAINT [pk_EQUIPMENT] NOT NULL PRIMARY KEY AUTOINCREMENT,  \
         [Name] VARCHAR( 45 ) NULL,                                     \
         [Description] VARCHAR( 45 ) NULL,  \
         [Type] VARCHAR( 45 ) NULL,\
         [EMC_Protection] VARCHAR( 45 ) NULL,\
         [Zone] VARCHAR( 45 ) NULL,\
         [FIN] VARCHAR( 45 ) NULL\
        );\n\
    ";

};
#endif // SQL_DATABASE_H
