cmake_minimum_required(VERSION 3.26)
project(UniversalConvertor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(UniversalConvertor main.cpp
        Convertor.cpp
        Convertor.h
        header.h
        Number.cpp
        Number.h
        App.cpp
        App.h
        Fraction.cpp
        Fraction.h
)

target_link_libraries(UniversalConvertor
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

