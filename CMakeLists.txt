cmake_minimum_required(VERSION 3.16)

project(AutoNota VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick WebEngineQuick)

qt_standard_project_setup()
qt_policy(SET QTP0001 NEW)

qt_add_executable(
    appAutoNota
    main.cpp
)

qt_add_qml_module(
    appAutoNota
    URI AutoNota
    VERSION 1.0
    QML_FILES
        Views/Main.qml
        Views/UsersDialog.qml
        Views/CreateUserDialog.qml
    SOURCES
        Models/user.h Models/user.cpp
        ItemModels/usersitemmodel.h ItemModels/usersitemmodel.cpp
)

target_include_directories(
    appAutoNota
    PRIVATE
        Models/
        ItemModels/
)

set_target_properties(
    appAutoNota
    PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(
    appAutoNota
    PRIVATE
        Qt6::Quick
        Qt6::WebEngineQuick
)

install(
    TARGETS appAutoNota
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
