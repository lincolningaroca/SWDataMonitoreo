#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dbconection.h"
#include "bussineslayer.h"
//inclusion del formulario nuevo cliente
#include "nuevodialog.h"
//inclusion del formulario nuevo catos monitoreo
#include "nuevaestmonitoreodialog.h"

//cabecera para cambio de tema oscuro
#include "qeasysettings.hpp"
#include<QComboBox>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:


  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void loadGpoMinerolist();
  void loadDataListCliente();
  void loadDataEstMonitoreo();
//  int getIdGrupo(QString name);

  void loadCboTemas();



private slots:
  void on_toolButton_clicked();
  void on_toolButton_2_clicked();
  void on_cboGrupo_activated(int index);

//  void on_rbPorFecha_clicked();

  void on_actionNuevo_punto_de_monitoreo_triggered();
  void on_toolButton_3_clicked();
  void on_cboUnidad_activated(int index);
//  void on_dePorFecha_userDateChanged(const QDate &date);
  void on_cboMeses_activated(int index);
  void on_cboAnios_activated(int index);

  void on_lwEstaciones_itemClicked(QListWidgetItem *item);



  void on_lwFotos_itemClicked(QListWidgetItem *item);

private:
  Ui::MainWindow *ui;

  DbConection db;
  BussinesLayer bLayer;
  //puntero de tipo nuevo cliente
  NuevoDialog *nuevoFrm;
  //puntero de tipo nuevo datos monitoreo
  NuevaEstMonitoreoDialog *nuevaEstFrm;
  QHash<int,QString> dataList;
  QHash<int,QString> dataListCliente;

  QComboBox *cboTemas;

  QHash<int,QString> meses;
  QHash<int,QString> dataList_2;
  int anio;
  QByteArray foto_1;
  QByteArray foto_2;
  QByteArray foto_3;

  //funciones y metodos privados
  void loadMesesAnios();
};
#endif // MAINWINDOW_H
