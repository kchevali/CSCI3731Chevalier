cmake_minimum_required(VERSION 3.0)
project(main.exe)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCE ../main.cpp
    ../angle.h
    ../angle.cpp
    ../fish.h
    ../fish.cpp
    ../smartfish.h
    ../smartfish.cpp
    ../drunkenfish.h
    ../drunkenfish.cpp
    ../flippyfish.h
    ../flippyfish.cpp
    ../population.h
    ../population.cpp
    ../mywidget.h
    ../mywidget.cpp
    ../vector.h
    ../vector.cpp
)
add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)