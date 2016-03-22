#ifndef ACICD_CONNECTOR_H
#define ACICD_CONNECTOR_H

#include <string>
#include <QString>
#include <map>

class acicd_connector
{
public:
    acicd_connector();
};

const QString DB_QUERY_CREATE_CONNECTOR="\
    CREATE TABLE IF NOT EXISTS [CONNECTOR](\
     [id] INTEGER CONSTRAINT [pk_CONNECTOR] PRIMARY KEY  NOT NULL,\
      [Equipment] INTEGER NULL,\
      [ACICD] INTEGER NULL,\
      [Type] VARCHAR( 45 ) NULL,\
      [Name] VARCHAR( 45 ) NULL,\
      [Pin] VARCHAR( 45 ) NULL,\
      [Pin_Role] INTEGER NULL,\
      [Connection_Name] INTEGER NULL,\
      [Line_Type] INTEGER NULL,\
      [Speed] INTEGER NULL,\
      [NetworkId] VARCHAR( 3 ) NULL,\
       CONSTRAINT [Equipment]\
       FOREIGN KEY([Equipment])\
         REFERENCES [EQUIPMENT] ( [id] ),\
       CONSTRAINT [ACICD]\
       FOREIGN KEY([ACICD])\
         REFERENCES [ACICD] ( [id] ),\
       CONSTRAINT [Pin_Role]\
       FOREIGN KEY([Pin_Role])\
         REFERENCES [Connector_Pin_Role] ( [id] ),\
       CONSTRAINT [Line_Type]\
       FOREIGN KEY([Line_Type])\
         REFERENCES [Connector_Line_type] ( [id] ),\
       CONSTRAINT [Connection_Name]\
       FOREIGN KEY([Connection_Name])\
         REFERENCES [Connection_Name] ( [id] )\
    );\n\
 ";


const QString DB_QUERY_CREATE_Connector_Line_type="\
        CREATE TABLE IF NOT EXISTS [Connector_Line_type](\
         [id] INTEGER CONSTRAINT [pk_Connector_Line_type] PRIMARY KEY  NOT NULL,  \
         [Name] VARCHAR( 45 ) NULL\
        );\n\
 ";

const QString DB_QUERY_CREATE_Connector_Pin_Role="\
        CREATE TABLE IF NOT EXISTS [Connector_Pin_Role](\
         [id] INTEGER CONSTRAINT [pk_Connector_Pin_Role] PRIMARY KEY  NOT NULL,\
         [Name] VARCHAR( 45 ) NULL\
        );\n\
 ";

const QString DB_QUERY_CREATE_Connection_Name="\
        CREATE TABLE IF NOT EXISTS [Connection_Name](\
         [id] INTEGER CONSTRAINT [pk_Connection_Name] PRIMARY KEY  NOT NULL,\
         [Name] VARCHAR( 45 ) NULL\
        );\n\
 ";

#endif // ACICD_CONNECTOR_H
