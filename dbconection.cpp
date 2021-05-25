#include "dbconection.h"

DbConection::DbConection(QObject *parent) : QObject(parent)
{

}

bool DbConection::getConection()
{
  db=QSqlDatabase::addDatabase("QPSQL");
  if(!db.isDriverAvailable("QPSQL")){
    _errorMessage=db.lastError().driverText();
    return false;
  }
  db.setDatabaseName("monitoreo_db");
  db.setHostName("localhost");
  db.setPassword("2311046");
  db.setPort(5432);
  db.setUserName("postgres");
  if(!db.open()){
    _errorMessage=db.lastError().databaseText();
    return false;
  }
  return true;

}

void DbConection::closeConection()
{
  if(db.isOpen())
    db.close();

}
