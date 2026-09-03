cmake_minimum_required(VERSION 3.16)

project(OrderManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

qt_standard_project_setup()

qt_add_executable(OrderManager
    src/main.cpp
    src/ui/MainWindow.cpp
    src/models/Product.cpp
    src/models/ProductsManager.cpp
    src/ui/ProductDialog.cpp
    src/ui/ProductItemWidget.cpp
    src/storage/JsonStorage.cpp
    src/database/Database.cpp
    src/repositories/ProductRepository.cpp
)

qt_add_resources(OrderManager "OrderManagerResources"
    PREFIX "/"
    FILES
        assets/styles/main.qss
)

target_include_directories(OrderManager PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(OrderManager PRIVATE Qt6::Widgets Qt6::Sql)

include(GNUInstallDirs)
install(TARGETS OrderManager
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    BUNDLE DESTINATION .
)

if(WIN32)
    qt_generate_deploy_app_script(
        TARGET OrderManager
        OUTPUT_SCRIPT deploy_script
        NO_TRANSLATIONS
    )
    install(SCRIPT ${deploy_script})
endif()

set(CPACK_PACKAGE_NAME "OrderManager")
set(CPACK_PACKAGE_VENDOR "OrderManager")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Desktop product order manager")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "OrderManager")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

if(WIN32)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_PACKAGE_FILE_NAME "OrderManager_Installer")
    set(CPACK_NSIS_DISPLAY_NAME "OrderManager")
    set(CPACK_NSIS_PACKAGE_NAME "OrderManager")
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
elseif(UNIX)
    set(CPACK_GENERATOR "RPM")
    set(CPACK_RPM_PACKAGE_REQUIRES "qt6-qtbase,qt6-qtbase-gui,qt6-qtbase-sqlite")
endif()

include(CPack)
