#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QListWidgetItem>
//cabecera para cambio de tema oscuro
#include "qeasysettings.hpp"
#include "editdatadialog.h"
#include "bussineslayer.h"
//inclusion del formulario nuevo cliente
#include "nuevodialog.h"
//inclusion del formulario nuevo catos monitoreo
#include "nuevaestmonitoreodialog.h"

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
  void saveImageContextMenu();
  void loadCboTemas();
  static MainWindow *getInstance();
  void haveData();


private slots:
  void on_toolButton_clicked();
  void on_toolButton_2_clicked();
  void on_cboGrupo_activated(int index);
  void on_actionNuevo_punto_de_monitoreo_triggered();
  void on_cboUnidad_activated(int index);
  void on_cboMeses_activated(int index);
  void on_cboAnios_activated(int index);
  void on_actionActualizar_datos_triggered();
  void on_actionEditar_datos_unidad_minera_triggered();
  void on_actioneditar_datos_monitoreo_triggered();
  void on_lwEstaciones_itemSelectionChanged();
  void on_lwFotos_itemSelectionChanged();

private:
  Ui::MainWindow *ui;
  BussinesLayer bLayer;
  //puntero de tipo nuevo cliente
  NuevoDialog *nuevoFrm;
  //puntero de tipo nuevo datos monitoreo
  NuevaEstMonitoreoDialog *nuevaEstFrm;
  QHash<int,QString> dataList;
  QVariantList dataList_monitoreo;
  QHash<int,QString> dataListCliente;
  QComboBox *cboTemas;
  QHash<int,QString> meses;
  QHash<int,QString> dataList_2;
  int anio;
  QImage foto_1;
  QImage foto_2;
  QImage foto_3;
  static MainWindow *instance;

  void loadMesesAnios();
  void loadSettings();
  void datosMonitoreo();
  void cleanControls();
  void defaultImage();
  QImage openPicture(QString f);
  void showFotoToControl(QListWidgetItem *item);

  // QPaintDevice interface
public:
  virtual QPaintEngine *paintEngine() const override;

  // QWidget interface
protected:
  virtual void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
