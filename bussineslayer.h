#ifndef BUSSINESLAYER_H
#define BUSSINESLAYER_H

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include "dbconection.h"


class BussinesLayer : public QObject
{

public:
  enum TypeStm{
    INSERT,
    UPDATE,
    DELETE
  };
  enum Table{
    GPO_MINERO,
    CLIENTE,
    MONITOREO,
    PARAMETROS
  };

  BussinesLayer();

  bool gpoMineroAction(QVariantList param, TypeStm modo);
  bool clienteMineroAction(QVariantList param, TypeStm modo);
  bool monitoreoMineroAction(QVariantList param, TypeStm modo);
  bool parametroAction(QVariantList param, TypeStm modo);
  QString errorMessage(){return _errorMessage;}
  QString errorCode(){return _errorCode;}
  QVariant lInsertId(){return _lInsertId;}
  QVariantList selectData(QVariant id, Table info);
  QVariantList dataEstMonitoreo(int nro);
  QHash<int, QString> selectCodEstacion(int cod);
  QHash<int, QString> selectCodEstacion(int cod, QString fecha);
  QHash<int, QString> selectCodEstacion(int anio, int mes, int id_cliente);
  QHash<int, QString> gpoMineroList(Table t, int id=0);
  QSqlQueryModel *data(int id);

  int nro(int codEstacion);


  QStringList completerList();
  bool getConnection();
//  bool nameValidate(QString name);

signals:
private:
//  QSqlDatabase db;
  DbConection db;
  QString _errorMessage;
  QString _errorCode;
  QVariant _lInsertId;
  QSqlQueryModel *model;

};

#endif // BUSSINESLAYER_H
