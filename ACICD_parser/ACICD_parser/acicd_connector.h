#ifndef ACICD_CONNECTOR_H
#define ACICD_CONNECTOR_H

#include <string>
#include <QString>
#include <map>

class acicd_connector
{
public:
    acicd_connector();

private:

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


};



#endif // ACICD_CONNECTOR_H
