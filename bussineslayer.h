#ifndef BUSSINESLAYER_H
#define BUSSINESLAYER_H
#include "dbconection.h"
#include <QSqlQuery>
#include <QSqlError>

#include <QObject>

class BussinesLayer : public QObject
{
  Q_OBJECT
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

  explicit BussinesLayer(QObject *parent = nullptr);

  bool gpoMineroAction(QStringList param, TypeStm modo);
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
  int nro(int codEstacion);

  QStringList completerList();
//  bool nameValidate(QString name);

signals:
private:
  DbConection db;
  QString _errorMessage;
  QString _errorCode;
  QVariant _lInsertId;


};

#endif // BUSSINESLAYER_H
