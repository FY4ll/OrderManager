cmake_minimum_required(VERSION 3.16)

project(OrderManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(OrderManager
    src/main.cpp
    src/MainWindow.cpp
    include/MainWindow.h
)

target_link_libraries(OrderManager PRIVATE Qt6::Widgets)