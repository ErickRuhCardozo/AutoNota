cmake_minimum_required(VERSION 3.16)

project(AutoNota VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick QuickControls2 WebEngineQuick Sql Svg)

qt_standard_project_setup()
qt_policy(SET QTP0001 NEW)

qt_add_executable(
    appAutoNota
        main.cpp
        Assets/autonota.rc
)

qt_add_qml_module(
    appAutoNota
        URI AutoNota
        VERSION 1.0
        QML_FILES
            Views/Main.qml
            Views/UsersDialog.qml
            Views/CreateUserDialog.qml
            Views/SettingsDialog.qml
            Views/InfoDialog.qml
        SOURCES
            Models/user.h Models/user.cpp
            ItemModels/usersitemmodel.h ItemModels/usersitemmodel.cpp
            Managers/loginmanager.h Managers/loginmanager.cpp
            Managers/donationmanager.h Managers/donationmanager.cpp
            Managers/settingsmanager.h Managers/settingsmanager.cpp
)

qt_add_resources(
    appAutoNota
        PREFIX "/"
        BASE "Assets"
        FILES
            Assets/qtquickcontrols2.conf
            Assets/Icons/user-minus.svg
            Assets/Icons/user-login.svg
            Assets/Icons/user-plus.svg
            Assets/Icons/users.svg
            Assets/Icons/gear.svg
            Assets/Icons/undo.svg
            Assets/Icons/info.svg
            Assets/Icons/app.svg
            Assets/Images/1.png
            Assets/Images/2.png
            Assets/Images/3.png
            Assets/Images/4.png
            Assets/index.html
            Assets/app.db
)

target_include_directories(
    appAutoNota
        PRIVATE
            Models/
            ItemModels/
            Managers/
)

set_target_properties(
    appAutoNota
        PROPERTIES
            MACOSX_BUNDLE_GUI_IDENTIFIER erickruhcardozo.autonota
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
            Qt6::Sql
            Qt6::Svg
            Qt6::WebEngineQuick
            Qt6::WebEngineQuickPrivate # This mf took me 3 hours... Thanks to: https://forum.qt.io/topic/127489/private-headers-access/6
)

install(
    TARGETS appAutoNota
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
