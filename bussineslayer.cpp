#include "bussineslayer.h"

BussinesLayer::BussinesLayer(QObject *parent) : QObject(parent)
{

}

bool BussinesLayer::gpoMineroAction(QStringList param, TypeStm modo)
{
  if(!db.getConection()){
    _errorMessage=db.errorMessage();
    return false;
  }
  QSqlQuery qry;

  switch (modo) {
    case INSERT:
      qry.prepare("INSERT INTO grupo_minero(nombre_grupo, descripcion) "
                  "VALUES(?,?)");
      for(int i=0;i<param.size();i++){
        qry.addBindValue(param[i]);
      }
      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return false;
      }

      break;

    case UPDATE:
      qry.prepare("UPDATE grupo_minero SET nombre_grupo=?,descripcion=? WHERE id=?");
      for(int i=0;i<param.size();++i){
        qry.addBindValue(param[i]);
        if(i==param.size())
          qry.addBindValue(param[i].toInt());
      }
      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return false;
      }
      break;

    case DELETE:
      qry.prepare("DELETE FROM grupo_minero WHERE id=?");
      qry.addBindValue(param[0].toInt(),QSql::In);

      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return false;
      }
      break;

  }
  qry.finish();
  db.closeConection();
  return true;
}

bool BussinesLayer::clienteMineroAction(QVariantList param, TypeStm modo)
{
  if(!db.getConection()){
    _errorMessage=db.errorMessage();
    return false;
  }
  QSqlQuery qry;

  switch (modo) {
    case INSERT:
      qry.prepare("INSERT INTO cliente(nombre_unidad, descripcion, id_grupo) "
                  "VALUES(?,?,?)");
      for(int i=0;i<param.size();i++){
        qry.addBindValue(param[i]);
        //        if(i==param.size())
        //          qry.addBindValue(param[i].toInt());
      }
      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return false;
      }

      break;

    case UPDATE:
      qry.prepare("UPDATE cliente SET nombre_grupo=?,descripcion=?, id_grupo=? WHERE id=?");
      for(int i=0;i<param.size();++i){
        qry.addBindValue(param[i]);
        //        if(i==param.size())
        //          qry.addBindValue(param[i].toInt());
      }
      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return false;
      }
      break;

    case DELETE:
      qry.prepare("DELETE FROM cliente WHERE id=?");
      qry.addBindValue(param[0].toInt(),QSql::In);

      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return false;
      }
      break;

  }
  qry.finish();
  db.closeConection();
  return true;
}

bool BussinesLayer::monitoreoMineroAction(QVariantList param, TypeStm modo)
{
  if(!db.getConection()){
    _errorMessage=db.errorMessage();
    return false;
  }
  QSqlQuery qry;

  switch (modo) {
    case INSERT:
      qry.prepare("INSERT INTO datos_monitoreo(codigo_estacion, fecha_muestra,hora_muestra,"
                  " descripcion, foto_1, foto_2, foto3, id_cliente)"
                  "VALUES(?,?,?,?,?,?,?,?)");
      //      qry.prepare("select datos_monit(?,?,?,?,?,?,?,?)");
      for(int i=0;i<param.size();i++){
        qry.addBindValue(param[i]);
        //        if(i==param.size())
        //          qry.addBindValue(param[i].toInt());

      }
      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return false;
      }
//      qry.next();
      _lInsertId=qry.lastInsertId();
      break;

    case UPDATE:
      qry.prepare("UPDATE datos_monitoreo SET fecha_muestra=?, hora_muestra=?, "
                  "descripcion=?, foto_1=?, foto_2=?, foto_3=?, id_cliente=? "
                  "WHERE codigo_estacion=?");
      for(int i=0;i<param.size();++i){
        qry.addBindValue(param[i]);
        //        if(i==param.size())
        //          qry.addBindValue(param[i].toInt());
      }
      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return false;
      }
      break;

    case DELETE:
      qry.prepare("DELETE FROM datos_monitoreo WHERE codigo_estacion=?");
      qry.addBindValue(param[0].toInt(),QSql::In);

      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return false;
      }
      break;

  }
  qry.finish();
  db.closeConection();
  return true;
}

bool BussinesLayer::parametroAction(QVariantList param, TypeStm modo)
{
  if(!db.getConection()){
    _errorMessage=db.errorMessage();
    return false;
  }
  QSqlQuery qry;

  switch (modo) {
    case INSERT:
      qry.prepare("INSERT INTO parametro_campo(ph, tem, od, ce, id_est) "
                  "VALUES(?,?,?,?,?)");
      for(int i=0;i<param.size();i++){
        qry.addBindValue(param[i]);
        //        if(i==param.size())
        //          qry.addBindValue(param[i].toInt());
      }
      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return false;
      }

      break;

    case UPDATE:
      qry.prepare("UPDATE parametro_campo SET ph=?, tem=?, od=?, ce=?, id_estacion=? "
                  "WHERE nro=? and id_estacion=?");
      for(int i=0;i<param.size();++i){
        qry.addBindValue(param[i]);
        //        if(i==param.size())
        //          qry.addBindValue(param[i].toInt());
      }
      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return false;
      }
      break;

    case DELETE:
      qry.prepare("DELETE FROM parametro_campo WHERE nro=? and id_estacion=?");
      qry.addBindValue(param[0].toInt(),QSql::In);
      qry.addBindValue(param[1].toString(),QSql::In);

      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return false;
      }
      break;

  }
  qry.finish();
  db.closeConection();
  return true;
}

QVariantList BussinesLayer::selectData(QVariant id, Table info)
{
  QVariantList dataList;
  if(!db.getConection()){
    _errorMessage=db.errorMessage();
    return dataList;
  }
  QSqlQuery qry;

  switch (info) {
    case GPO_MINERO:
      qry.prepare("SELECT * FROM grupo_minero WHERE id=?");
      qry.addBindValue(id);
      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        //        dataList.clear();
        return dataList;

      }
      while(qry.next()){
        dataList.append(qry.value(0));
        dataList.append(qry.value(1));
        dataList.append(qry.value(2));
      }
      break;
    case CLIENTE:
      qry.prepare("SELECT * FROM cliente WHERE id=?");
      qry.addBindValue(id);
      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        return dataList;
      }
      while(qry.next()){
        dataList.append(qry.value(0));
        dataList.append(qry.value(1));
        dataList.append(qry.value(2));
        dataList.append(qry.value(3));
      }
      break;
    case MONITOREO:
      qry.prepare("SELECT * FROM datos_monitoreo WHERE id=?");
      qry.addBindValue(id);
      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        return dataList;
      }
      while(qry.next()){
        dataList.append(qry.value(0));
        dataList.append(qry.value(1));
        dataList.append(qry.value(2));
        dataList.append(qry.value(3));
        dataList.append(qry.value(4));
        dataList.append(qry.value(5));
        dataList.append(qry.value(6));
        dataList.append(qry.value(7));
      }
      break;
    case PARAMETROS:
      qry.prepare("SELECT * FROM parametro_campo WHERE id=?");
      qry.addBindValue(id);
      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        return dataList;
      }
      while(qry.next()){
        dataList.append(qry.value(0));
        dataList.append(qry.value(1));
        dataList.append(qry.value(2));
        dataList.append(qry.value(3));
        dataList.append(qry.value(4));
        dataList.append(qry.value(5));
      }
      break;

  }
  qry.finish();
  db.closeConection();
  return dataList;

}

QHash<int,QString> BussinesLayer::selectCodEstacion(int cod)
{
  QHash<int,QString> dataList;
  if(!db.getConection()){
    _errorMessage=db.errorMessage();

    return dataList;
  }
  QSqlQuery qry;
  qry.prepare("SELECT id_estacion,codigo_estacion FROM datos_monitoreo WHERE id_cliente=?");
  qry.addBindValue(cod);
//  qry.addBindValue(fecha);
  if(!qry.exec()){
    _errorMessage=qry.lastError().text();
    _errorCode=qry.lastError().nativeErrorCode();
    return dataList;
  }
  while(qry.next()){
    dataList.insert(qry.value(0).toInt(),qry.value(1).toString());
  }

  qry.finish();
  db.closeConection();
  return dataList;
}

QHash<int, QString> BussinesLayer::selectCodEstacion(int cod, QString fecha)
{
  QHash<int,QString> dataList;
  if(!db.getConection()){
    _errorMessage=db.errorMessage();

    return dataList;
  }
  QSqlQuery qry;
  qry.prepare("SELECT id_estacion,codigo_estacion FROM datos_monitoreo WHERE id_cliente=?"
              " AND fecha_muestra=?");
  qry.addBindValue(cod);
  qry.addBindValue(fecha);
  if(!qry.exec()){
    _errorMessage=qry.lastError().text();
    _errorCode=qry.lastError().nativeErrorCode();
    return dataList;
  }
  while(qry.next()){
    dataList.insert(qry.value(0).toInt(),qry.value(1).toString());
  }

  qry.finish();
  db.closeConection();
  return dataList;
}

QHash<int,QString> BussinesLayer::gpoMineroList(Table t, int id)
{
  QHash<int,QString> dataList;
  if(!db.getConection()){
    _errorMessage=db.errorMessage();

    return dataList;
  }
  QSqlQuery qry;
  //  dataList.clear();
  switch (t) {
    case GPO_MINERO:

      qry.prepare("SELECT id, nombre_grupo FROM grupo_minero");
      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return dataList;
      }
      while(qry.next()){
        dataList.insert(qry.value(0).toInt(),qry.value(1).toString());
      }
      //      return dataList;
      break;

    case CLIENTE:
      //      QSqlQuery qry;
      qry.prepare("SELECT id, nombre_unidad FROM cliente WHERE id_grupo=?");
      qry.addBindValue(id);
      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return dataList;
      }
      while(qry.next()){
        dataList.insert(qry.value(0).toInt(),qry.value(1).toString());
      }
      //      return dataList;
      break;

    default:
      return dataList;
      break;
  }
  qry.finish();
  db.closeConection();

  return dataList;

}

QStringList BussinesLayer::completerList()
{
  QStringList dataList;
  if(!db.getConection()){
    _errorMessage=db.errorMessage();

    return dataList;
  }
  QSqlQuery qry;
  qry.prepare("SELECT codigo_estacion FROM datos_monitoreo");

  if(!qry.exec()){
    _errorMessage=qry.lastError().text();
    _errorCode=qry.lastError().nativeErrorCode();
    return dataList;
  }
  while(qry.next()){
    dataList.append(qry.value(0).toString().trimmed());
  }
  qry.finish();
  db.closeConection();
  return dataList;
}

