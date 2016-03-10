#include <iostream>
#include <string>
#include <fstream>

#include "csv_parser.h"
#include "csv_stl_traits.h"
#include "csv_data.h"
#include <boost/optional/optional_io.hpp>

#include "acicd_header.h"
#include "mysql_database.h"

#include <QtSql>

#define q2c(string) string.toStdString()

using namespace std;

template<typename parser_>
void parsefile(std::fstream& f, parser_& parser)
{
    char buf[16192];
    while(f.good() && !parser.error())
    {
        int nb = sizeof(buf);
        f.read(buf, nb);
        if(!f.good())
            nb = f.gcount();

        for(int i = 0; i < nb; ++i)
        {
            parser.consume(buf[i]);
           // std::cout << buf[i];
        }
    }
    if(f.eof())
        parser.end_of_data();
}

int main(int argc, char** argv)
{
    std::string file;

    dvp::csv_parser<dvp::csv_stl_traits> parser;

    //handler<std::string> h(parser);
    dvp::csv_data data;

    dvp::acicd_data_handler handler(data, true, parser);

    std::vector<std::string> vect_header;
    std::vector<std::string>::iterator it_header;

    if(argc <= 1)
            file = "acicd.csv";
        else
            file = argv[1];



    std::fstream f(file);

    parsefile(f, parser);
    std::cout << //h.nbfields
            data.size()
 //           << " " << h.nblines
            << std::endl;
//    int i=0;

//    dvp::csv_data::const_iterator it;
//    std::vector<std::string>::const_iterator it_record;


//    for(it=data.begin();it!=data.end();++it)
//    {
//       if((*it)[0].compare(key_word_begin_data_section)==0)
//       {
//            ++it;
//            std::cout <<(*it)[0] << std::endl;
//       }


//       for(it_record=it->begin();it_record!=it->end();++it_record)
//       {
//           // std::cout <<"test nasa:" +   *it_record   << std::endl;
//       }
//   }





//    std::string db_name="INTEGRATOR_WORKSHOP";
//    mysql_database BDD;
//    QSqlDatabase db=BDD.set_database(db_name);


//    if(db.open())
//    {
//        std::cout << "Vous etes maintenant connecte a " << q2c(db.hostName()) << std::endl;
//    }
//    else
//    {
//        std::cout << "La connexion a echouee" << std::endl;
//    }
//    QSqlQuery query(db);

//    query.prepare("CREATE TABLE IF NOT EXISTS `mydb`.`EQUIPMENT`");
//    if(query.isValid())
//    {

//        std::cout << "Requete valide" << std::endl;
//    }
//    else
//    {
//        std::cout << "*** Error ***" << std::endl;
//        std::cout << "MySQL error:" << std::endl << q2c(query.lastError().text()) << std::endl;
//        std::cout << "MySQL error code:" << std::endl << q2c(QString::number(query.lastError().number())) << std::endl;
//    }


      QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

      db.setHostName( "localhost" );
      db.setDatabaseName( "qtbook.db" );

      db.setUserName( "root" );
      db.setPassword( "sa" );

      if( !db.open() )
      {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
      }else{
        qDebug( "Connected!" );
      }


      QFile scriptFile("integrator_workshop.sql");
      QSqlQuery query;

      if (scriptFile.open(QIODevice::ReadOnly))
      {
          // The SQLite driver executes only a single (the first) query in the QSqlQuery
          //  if the script contains more queries, it needs to be splitted.
          QStringList scriptQueries = QTextStream(&scriptFile).readAll().split(';');

          foreach (QString queryTxt, scriptQueries)
          {
              if (queryTxt.trimmed().isEmpty()) {
                  continue;
              }
              if (!query.exec(queryTxt))
              {
                  qFatal(QString("One of the query failed to execute."
                              " Error detail: " + query.lastError().text()).toLocal8Bit());
              }
              query.finish();
          }
      }











//      QSqlQuery qry;

//      qry.prepare( "CREATE TABLE IF NOT EXISTS names (id INTEGER UNIQUE PRIMARY KEY, firstname VARCHAR(30), lastname VARCHAR(30))" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug() << "Table created!";

//      qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (1, 'John', 'Doe')" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (2, 'Jane', 'Doe')" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (3, 'James', 'Doe')" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (4, 'Judy', 'Doe')" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (5, 'Richard', 'Roe')" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (6, 'Jane', 'Roe')" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (7, 'John', 'Noakes')" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (8, 'Donna', 'Doe')" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (9, 'Ralph', 'Roe')" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//    // SALARIES
//      qry.prepare( "CREATE TABLE IF NOT EXISTS salaries (id INTEGER UNIQUE PRIMARY KEY, annual INTEGER)" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO salaries (id, annual) VALUES (1, 1000)" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO salaries (id, annual) VALUES (2, 900)" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO salaries (id, annual) VALUES (3, 900)" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO salaries (id, annual) VALUES (5, 1100)" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO salaries (id, annual) VALUES (6, 1000)" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO salaries (id, annual) VALUES (8, 1200)" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "INSERT INTO salaries (id, annual) VALUES (9, 1200)" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Inserted!" );

//      qry.prepare( "SELECT * FROM salaries" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//      {
//        qDebug( "Selected!" );

//        QSqlRecord rec = qry.record();
//        int cols = rec.count();

//        QString temp;
//        for( int c=0; c<cols; c++ )
//          temp += rec.fieldName(c) + ((c<cols-1)?"\t":"");
//        qDebug() << temp;

//        while( qry.next() )
//        {
//          temp = "";
//          for( int c=0; c<cols; c++ )
//            temp += qry.value(c).toString() + ((c<cols-1)?"\t":"");
//          qDebug() << temp;
//        }
//      }

//      qry.prepare( "SELECT names.firstname, names.lastname, salaries.annual FROM names JOIN salaries ON names.id = salaries.id" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//      {
//        qDebug( "Selected!" );

//        QSqlRecord rec = qry.record();
//        int cols = rec.count();

//        QString temp;
//        for( int c=0; c<cols; c++ )
//          temp += rec.fieldName(c) + ((c<cols-1)?"\t":"");
//        qDebug() << temp;

//        while( qry.next() )
//        {
//          temp = "";
//          for( int c=0; c<cols; c++ )
//            temp += qry.value(c).toString() + ((c<cols-1)?"\t":"");
//          qDebug() << temp;
//        }
//      }

//      qry.prepare( "SELECT names.firstname, names.lastname, salaries.annual FROM names LEFT JOIN salaries ON names.id = salaries.id" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//      {
//        qDebug( "Selected!" );

//        QSqlRecord rec = qry.record();
//        int cols = rec.count();

//        QString temp;
//        for( int c=0; c<cols; c++ )
//          temp += rec.fieldName(c) + ((c<cols-1)?"\t":"");
//        qDebug() << temp;

//        while( qry.next() )
//        {
//          temp = "";
//          for( int c=0; c<cols; c++ )
//            temp += qry.value(c).toString() + ((c<cols-1)?"\t":"");
//          qDebug() << temp;
//        }
//      }

//      qry.prepare( "SELECT names.lastname, SUM(salaries.annual)/COUNT(*) AS 'Average', MIN(salaries.annual) AS 'Minimum', MAX(salaries.annual) AS 'Maximum' FROM names LEFT JOIN salaries ON names.id = salaries.id GROUP BY names.lastname" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//      {
//        qDebug( "Selected!" );

//        QSqlRecord rec = qry.record();
//        int cols = rec.count();

//        QString temp;
//        for( int c=0; c<cols; c++ )
//          temp += rec.fieldName(c) + ((c<cols-1)?"\t":"");
//        qDebug() << temp;

//        while( qry.next() )
//        {
//          temp = "";
//          for( int c=0; c<cols; c++ )
//            temp += qry.value(c).toString() + ((c<cols-1)?"\t":"");
//          qDebug() << temp;
//        }
//      }
//    // SALARIES

//      qry.prepare( "SELECT * FROM names" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//      {
//        qDebug( "Selected!" );

//        QSqlRecord rec = qry.record();

//        int cols = rec.count();

//        for( int c=0; c<cols; c++ )
//          qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );

//        for( int r=0; qry.next(); r++ )
//          for( int c=0; c<cols; c++ )
//            qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
//      }


//      qry.prepare( "SELECT firstname, lastname FROM names WHERE lastname = 'Roe'" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//      {
//        qDebug( "Selected!" );

//        QSqlRecord rec = qry.record();

//        int cols = rec.count();

//        for( int c=0; c<cols; c++ )
//          qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );

//        for( int r=0; qry.next(); r++ )
//          for( int c=0; c<cols; c++ )
//            qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
//      }


//      qry.prepare( "SELECT firstname, lastname FROM names WHERE lastname = 'Roe' ORDER BY firstname" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//      {
//        qDebug( "Selected!" );

//        QSqlRecord rec = qry.record();

//        int cols = rec.count();

//        for( int c=0; c<cols; c++ )
//          qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );

//        for( int r=0; qry.next(); r++ )
//          for( int c=0; c<cols; c++ )
//            qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
//      }


//      qry.prepare( "SELECT lastname, COUNT(*) as 'members' FROM names GROUP BY lastname ORDER BY lastname" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//      {
//        qDebug( "Selected!" );

//        QSqlRecord rec = qry.record();

//        int cols = rec.count();

//        for( int c=0; c<cols; c++ )
//          qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );

//        for( int r=0; qry.next(); r++ )
//          for( int c=0; c<cols; c++ )
//            qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
//      }

//      qry.prepare( "UPDATE names SET firstname = 'Nisse', lastname = 'Svensson' WHERE id = 7" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Updated!" );

//      qry.prepare( "UPDATE names SET lastname = 'Johnson' WHERE firstname = 'Jane'" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Updated!" );

//      qry.prepare( "DELETE FROM names WHERE id = 7" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Deleted!" );

//      qry.prepare( "DELETE FROM names WHERE lastname = 'Johnson'" );
//      if( !qry.exec() )
//        qDebug() << qry.lastError();
//      else
//        qDebug( "Deleted!" );





    db.close();
    return 0;
}

