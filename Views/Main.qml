import QtQuick
import QtWebEngine
import QtQuick.Layouts
import QtQuick.Controls

ApplicationWindow {
    width: 800
    height: 450
    visible: true
    title: 'AutoNota - Desenvolvido por Erick Ruh Cardozo'
    header: ToolBar {
        ToolButton {
            text: 'Usuários'
            onClicked: usersDialogLoader.active = true
        }
    }

    Loader {
        id: usersDialogLoader
        source: 'UsersDialog.qml'
        active: false

        Connections {
            target: usersDialogLoader.item
            function onClosing() { usersDialogLoader.active = false }
        }
    }
}
