#include "mainwindow.h"

#include <QApplication>

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
  w.show();
  return a.exec();
}
