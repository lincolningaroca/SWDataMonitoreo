#ifndef DBCONECTION_H
#define DBCONECTION_H
#include <QSqlDatabase>
#include <QSqlError>

#include <QObject>

class DbConection : public QObject
{
  Q_OBJECT
public:
//  enum typeSentences{
//    INSERT,
//    UPDATE,
//    DELETE
//  };
  explicit DbConection();
  bool getConection();
  void closeConection();
  QString errorMessage(){return _errorMessage;}
//  bool execQuery(typeSentences type,QStringList param);

signals:
private:
  QSqlDatabase db;
  QString _errorMessage;

};

#endif // DBCONECTION_H
