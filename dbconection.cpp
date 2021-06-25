#include "dbconection.h"

DbConection::DbConection()
{

}

QSqlDatabase DbConection::getConection()
{
  db=QSqlDatabase::addDatabase("QPSQL");
  if(!db.isDriverAvailable("QPSQL")){
    _errorMessage=db.lastError().text();
    return db;
  }
  db.setDatabaseName("monitoreo_db");
  db.setHostName("localhost");
  db.setPassword("2311046");
  db.setPort(5432);
  db.setUserName("postgres");
  if(!db.open()){
    _errorMessage=db.lastError().databaseText();
    return db;
  }
  return db;

}
