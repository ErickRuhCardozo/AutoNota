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
            focusPolicy: Qt.NoFocus
            icon.source: 'qrc:/Assets/Icons/users.svg'
            ToolTip.visible: hovered
            ToolTip.text: 'Usuários'
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

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        TextField {
            Layout.fillWidth: true
            placeholderText: 'Chave de Acesso'
            focus: true
        }

        WebEngineView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            enabled: false
            url: 'about:blank'
        }
    }
}
