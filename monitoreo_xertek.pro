QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
  main.cpp\
  mainwindow.cpp\
  dbconection.cpp\
  swcustomtxt.cpp\
  bussineslayer.cpp\
  nuevodialog.cpp\
  nuevaestmonitoreodialog.cpp\
  qeasysettings.cpp\
  editdatadialog.cpp\
  desc_pdialog.cpp\
  fotodialog.cpp
HEADERS += \
  mainwindow.h\
  dbconection.h\
  swcustomtxt.h\
  bussineslayer.h\
  nuevodialog.h\
  nuevaestmonitoreodialog.h\
  qeasysettings.hpp\
  editdatadialog.h\
  desc_pdialog.h\  
  fotodialog.h
FORMS += \
  mainwindow.ui\
  nuevodialog.ui\
  nuevaestmonitoreodialog.ui\
  editdatadialog.ui\
  Desc_pdialog.ui\  
  fotodialog.ui
RESOURCES +=\
  rsc.qrc

RC_ICONS+=AppIcon/appIcon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
