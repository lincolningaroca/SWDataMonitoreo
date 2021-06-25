#include "dbconection.h"

QSqlDatabase db=QSqlDatabase::addDatabase("QPSQL");
DbConection::DbConection(){
}

QSqlDatabase DbConection::getConection()
{
  if(!db.isDriverAvailable("QPSQL")){
    _errorMessage=db.lastError().databaseText();
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
