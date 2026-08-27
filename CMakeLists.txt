cmake_minimum_required(VERSION 3.16)

project(OrderManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(OrderManager
    src/main.cpp
    src/ui/MainWindow.cpp
    src/models/Product.cpp
    src/models/ProductsManager.cpp
    src/ui/ProductDialog.cpp
    src/ui/ProductItemWidget.cpp
    src/storage/JsonStorage.cpp
)
target_include_directories(OrderManager PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(OrderManager PRIVATE Qt6::Widgets)
