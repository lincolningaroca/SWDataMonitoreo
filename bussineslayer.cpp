#include "bussineslayer.h"

BussinesLayer::BussinesLayer()
{
  db.getConection();
}

bool BussinesLayer::gpoMineroAction(QVariantList param, TypeStm modo)
{

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
  return true;
}

bool BussinesLayer::clienteMineroAction(QVariantList param, TypeStm modo)
{
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
      qry.prepare("UPDATE cliente SET nombre_unidad=?,descripcion=?, id_grupo=? WHERE id=?");
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
  return true;
}

bool BussinesLayer::monitoreoMineroAction(QVariantList param, TypeStm modo)
{

  QSqlQuery qry;

  switch (modo) {
    case INSERT:
      qry.prepare("INSERT INTO datos_monitoreo(codigo_estacion, fecha_muestra,hora_muestra,"
                  " descripcion, foto_1, foto_2, foto3, id_cliente, coor_este, coor_norte, cota,"
                  "desc_punto) VALUES(?,?,?,?,?,?,?,?,?,?,?,?)");

      for(int i=0;i<param.size();i++){
        qry.addBindValue(param[i]);

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
      qry.prepare("UPDATE datos_monitoreo SET codigo_estacion=?,fecha_muestra=?,hora_muestra=?,"
                  "descripcion=?,foto_1=?,foto_2=?,foto3=?,id_cliente=?,"
                  "coor_este=?,coor_norte=?,cota=?,desc_punto=? "
                  "WHERE id_estacion=?");
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
      qry.prepare("DELETE FROM datos_monitoreo WHERE id_estacion=?");
      qry.addBindValue(param[0].toInt(),QSql::In);

      if(!qry.exec()){
        _errorMessage=qry.lastError().text();
        _errorCode=qry.lastError().nativeErrorCode();
        return false;
      }
      break;

  }
  return true;
}

bool BussinesLayer::parametroAction(QVariantList param, TypeStm modo)
{
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
      qry.prepare("UPDATE parametro_campo SET ph=?,tem=?,od=?,ce=? "
                  "WHERE nro=? and id_est=?");

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
  return true;
}

QVariantList BussinesLayer::selectData(QVariant id, Table info)
{
  QVariantList dataList;
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
  return dataList;

}

QVariantList BussinesLayer::dataEstMonitoreo(int nro)
{
  QVariantList dataList;

  QSqlQuery qry;
  qry.prepare("SELECT codigo_estacion,fecha_muestra,hora_muestra,descripcion,"
              "foto_1,foto_2,foto3,id_cliente,coor_este,coor_norte,cota,"
              "desc_punto,nro,ph,tem,od,ce,id_est FROM "
              "datos_monitoreo dm  INNER JOIN parametro_campo pc "
              "ON dm.id_estacion=pc.id_est AND nro=?");
  //  qry.addBindValue(idEstacion);
  qry.addBindValue(nro);

  //  qry.addBindValue(fecha);
  if(!qry.exec()){
    _errorMessage=qry.lastError().text();
    _errorCode=qry.lastError().nativeErrorCode();
    return dataList;
  }
  qry.next();
  dataList.append(qry.value(0));
  dataList.append(qry.value(1));
  dataList.append(qry.value(2));
  dataList.append(qry.value(3));
  dataList.append(qry.value(4));
  dataList.append(qry.value(5));
  dataList.append(qry.value(6));
  dataList.append(qry.value(7));
  dataList.append(qry.value(8));
  dataList.append(qry.value(9));
  dataList.append(qry.value(10));
  dataList.append(qry.value(11));
  dataList.append(qry.value(12));
  dataList.append(qry.value(13));
  dataList.append(qry.value(14));
  dataList.append(qry.value(15));
  dataList.append(qry.value(16));
  return dataList;
}

QHash<int,QString> BussinesLayer::selectCodEstacion(int cod)
{
  QHash<int,QString> dataList;

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
  return dataList;
}

QHash<int, QString> BussinesLayer::selectCodEstacion(int cod, QString fecha)
{
  QHash<int,QString> dataList;

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
  return dataList;
}

QHash<int, QString> BussinesLayer::selectCodEstacion(int anio, int mes,int id_cliente)
{
  QHash<int,QString> dataList;

  QSqlQuery qry;
  qry.prepare("SELECT id_estacion, codigo_estacion FROM datos_monitoreo "
              " WHERE EXTRACT(YEAR FROM fecha_muestra)=? AND"
              " EXTRACT(MONTH FROM fecha_muestra)=? AND id_cliente=?");
  qry.addBindValue(anio);
  qry.addBindValue(mes);
  qry.addBindValue(id_cliente);
  if(!qry.exec()){
    _errorMessage=qry.lastError().text();
    _errorCode=qry.lastError().nativeErrorCode();
    return dataList;
  }
  while(qry.next()){
    dataList.insert(qry.value(0).toInt(),qry.value(1).toString());
  }
  return dataList;
}

QHash<int,QString> BussinesLayer::gpoMineroList(Table t, int id)
{
  QHash<int,QString> dataList;

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
  return dataList;
}
QSqlQueryModel *BussinesLayer::data(int id)
{
  QSqlQuery qry;
  qry.prepare("SELECT id_estacion, codigo_estacion, fecha_muestra, id_cliente "
              "FROM datos_monitoreo WHERE id_cliente=?;");
  qry.addBindValue(id);
  if(!qry.exec()){
    _errorMessage=qry.lastError().text();
    _errorCode=qry.lastError().nativeErrorCode();
    return model;
  }
  model=new QSqlQueryModel;
  model->setQuery(qry);
  qry.next();
  return model;

}


int BussinesLayer::nro(int codEstacion)
{
  int nro=0;

  QSqlQuery qry;
  qry.prepare("SELECT nro FROM parametro_campo WHERE id_est=?");
  qry.addBindValue(codEstacion);

  if(!qry.exec()){
    _errorMessage=qry.lastError().text();
    _errorCode=qry.lastError().nativeErrorCode();
    return nro;
  }
  qry.next();
  nro=qry.value(0).toInt();
  return nro;
}

QStringList BussinesLayer::completerList()
{
  QStringList dataList;

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
  return dataList;
}

