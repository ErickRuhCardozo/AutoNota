cmake_minimum_required(VERSION 3.16)

project(AutoNota VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick QuickControls2 WebEngineQuick)

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
            Views/AlertBox.qml
        SOURCES
            Models/user.h Models/user.cpp
            ItemModels/usersitemmodel.h ItemModels/usersitemmodel.cpp
            loginmanager.h loginmanager.cpp
            donator.h donator.cpp
)

qt_add_resources(
    appAutoNota
        PREFIX "/"
        FILES
            qtquickcontrols2.conf
            Assets/Icons/user-plus.svg
            Assets/Icons/user-minus.svg
            Assets/Icons/user-login.svg
            Assets/Icons/users.svg
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
            Qt6::QuickControls2
            Qt6::WebEngineCore
            Qt6::WebEngineQuick
            Qt6::WebEngineQuickPrivate # This mf took me 3 hours... Thanks to: https://forum.qt.io/topic/127489/private-headers-access/6
)

install(
    TARGETS appAutoNota
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
