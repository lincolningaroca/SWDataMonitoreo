cmake_minimum_required(VERSION 3.5)

project(monitoreo_xertek VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(APP_ICON"${CMAKE_CURRENT_SOURCE_DIR}/AppIcon/appIcon.rc")

#set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/include")
#set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")


#add_executable(${PROJECT_NAME} main.cpp ${APP_ICON})

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport REQUIRED)
find_package(Qt6 COMPONENTS Qml REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core5Compat REQUIRED)

#modulo sql
find_package(Qt6 COMPONENTS Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Sql REQUIRED)

#include_directories(${INC_DIR})
#link_directories(${LIB_DIR})
#link_libraries(LIMEREPO)

set(PROJECT_SOURCES
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  rsc.qrc
  dbconection.cpp
  dbconection.h
  #capa de negocios
  bussineslayer.cpp
  bussineslayer.h
  #formulario para agregar nuevos clientes
  nuevodialog.cpp
  nuevodialog.h
  nuevodialog.ui
  #formulario para agregar nueva estacion de monitoreo
  nuevaestmonitoreodialog.cpp
  nuevaestmonitoreodialog.h
  nuevaestmonitoreodialog.ui
  #libreria para modo oscuro de la aplicacion
  qeasysettings.cpp
  qeasysettings.hpp
  #formulario de actualizacion de datos para punto de monitoreo
  editdatadialog.cpp
  editdatadialog.h
  editdatadialog.ui
  #icono de la aplicacion
  AppIcon/appIcon.rc
  ${APPICON}
  )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable("${PROJECT_NAME}"
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}

    )
else()
  if(ANDROID)
    add_library("${PROJECT_NAME}" SHARED
      ${PROJECT_SOURCES}
      )
  else()
    add_executable("${PROJECT_NAME}"
      ${PROJECT_SOURCES}
      )
  endif()
endif()

target_link_libraries("${PROJECT_NAME}" PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#modeulo sql
target_link_libraries("${PROJECT_NAME}" PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
#target_link_libraries("${PROJECT_NAME}" PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)
#target_link_libraries("${PROJECT_NAME}" PRIVATE Qt${QT_VERSION_MAJOR}::Qml)
#target_link_libraries("${PROJECT_NAME}" PRIVATE Qt${QT_VERSION_MAJOR}::Core5Compat)

#target_link_libraries("${PROJECT_NAME}" PRIVATE LIMEREPO)

set_target_properties("${PROJECT_NAME}" PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  )
set_property(TARGET "${PROJECT_NAME}" PROPERTY WIN32_EXECUTABLE true)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable("${PROJECT_NAME}")
endif()
