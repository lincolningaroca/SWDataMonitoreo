#ifndef DBCONECTION_H
#define DBCONECTION_H
#include <QSqlDatabase>
#include <QSqlError>

class DbConection
{
public:
  DbConection();
  QSqlDatabase getConection();
  QString errorMessage(){return _errorMessage;}
//  void closeConection();

private:
  QString _errorMessage;

};

#endif // DBCONECTION_H
