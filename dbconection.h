#ifndef DBCONECTION_H
#define DBCONECTION_H
#include <QSqlDatabase>
#include <QSqlError>

class DbConection
{
public:
//  enum typeSentences{
//    INSERT,
//    UPDATE,
//    DELETE
//  };
  DbConection();
  QSqlDatabase getConection();
  QString errorMessage(){return _errorMessage;}
//  bool execQuery(typeSentences type,QStringList param);

private:
  QSqlDatabase db;
  QString _errorMessage;

};

#endif // DBCONECTION_H
