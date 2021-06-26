#include "mainwindow.h"

#include <QApplication>
#include <QStandardPaths>
#include <QDebug>
#include "bussineslayer.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setStyle("Fusion");
  a.setApplicationName("SWDatos_monitoreo");
  a.setApplicationVersion("1.0");
  a.setOrganizationName("SWSystem's");
  a.setOrganizationDomain("swsystems.com");
  MainWindow w;
  w.setWindowTitle(a.applicationName());
  //  w.setWindowState(Qt::WindowMaximized);
  BussinesLayer b;
  if(!b.createDirPictures())
    qDebug()<<"La carpeta ya existe";
  else
    qDebug()<<"La carpeta fue creada";

  //  w.getInstance()->show();

  //validar si ahy adtos en la Db--XdXdXd

  w.show();
  return a.exec();

}
