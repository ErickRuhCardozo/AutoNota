/*
 * Author: Erick Ruh Cardozo (https://github.com/erickruhcardozo)
 * Date: May 17, 2023 - 1:53 PM
 */

import QtQuick
import QtWebEngine
import QtQuick.Layouts
import QtQuick.Controls
import AutoNota

ApplicationWindow {
    width: 800
    height: 450
    visible: true
    title: 'AutoNota - Desenvolvido por Erick Ruh Cardozo'
    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            ToolButton {
                focusPolicy: Qt.NoFocus
                icon.source: 'qrc:/Assets/Icons/users.svg'
                ToolTip.visible: hovered
                ToolTip.text: 'Usuários'
                onClicked: usersDialogLoader.active = true
            }

            BusyIndicator {
                Layout.alignment: Qt.AlignRight
                Material.accent: Material.Yellow
                implicitHeight: parent.height
                visible: webView.loading
                running: webView.loading
            }
        }
    }

    LoginManager {
        id: loginManager
        webView: webView
    }

    Loader {
        id: usersDialogLoader
        source: 'UsersDialog.qml'
        active: false

        Connections {
            target: usersDialogLoader.item

            function onClosing() {
                usersDialogLoader.active = false
            }

            function onLoginRequested(ssn, password) {
                loginManager.login(ssn, password)
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        TextField {
            Layout.fillWidth: true
            placeholderText: 'Chave de Acesso'
            focus: true
            text: webView.url
        }

        WebEngineView {
            id: webView
            Layout.fillWidth: true
            Layout.fillHeight: true
//            enabled: false
        }
    }
}
