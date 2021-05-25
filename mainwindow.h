#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dbconection.h"
#include "bussineslayer.h"
//inclusion del formulario nuevo cliente
#include "nuevodialog.h"
//inclusion del formulario nuevo catos monitoreo
#include "nuevaestmonitoreodialog.h"
// cabecera autocompletado
#include <QCompleter>

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
//  int getIdGrupo(QString name);
  //metodo autocompleter
  void setCompleter();

private slots:
  void on_toolButton_clicked();
  void on_toolButton_2_clicked();
  void on_cboGrupo_activated(int index);
  void setUpBusqueda();
  void on_rbPorFecha_clicked();
  void on_rbPorNombre_clicked(bool checked);
  void on_actionNuevo_punto_de_monitoreo_triggered();
  void on_toolButton_3_clicked();
  void on_cboUnidad_activated(int index);
  void on_dePorFecha_userDateChanged(const QDate &date);

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
  //autocompletar
  QCompleter *completer;
};
#endif // MAINWINDOW_H
