cmake_minimum_required(VERSION 3.5)

project(monitoreo_xertek VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
#modulo sql
find_package(Qt6 COMPONENTS Sql REQUIRED)

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
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(monitoreo_xertek
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(monitoreo_xertek SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(monitoreo_xertek
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(monitoreo_xertek PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#modeulo sql
target_link_libraries(monitoreo_xertek PRIVATE Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(monitoreo_xertek PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(monitoreo_xertek)
endif()
