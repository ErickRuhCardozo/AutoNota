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
    title: 'AutoNota | Desenvolvido por Erick Ruh Cardozo'
    Component.onCompleted: {
        if (!isFirstRun && defaultSsn !== '') {
            loginManager.login(defaultUser, defaultSsn, defaultPassword)
        }
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            ToolButton {
                focusPolicy: Qt.NoFocus
                icon.source: 'qrc:/Icons/users.svg'
                ToolTip.visible: hovered
                ToolTip.text: 'Usuários'
                onClicked: usersDialogLoader.active = true
            }

            ToolButton {
                focusPolicy: Qt.NoFocus
                icon.source: 'qrc:/Icons/gear.svg'
                ToolTip.visible: hovered
                ToolTip.text: 'Configurações'
                onClicked: settingsDialogLoader.active = true
            }

            ToolButton {
                focusPolicy: Qt.NoFocus
                icon.source: 'qrc:/Icons/info.svg'
                ToolTip.visible: hovered
                ToolTip.text: 'Sobre'
                onClicked: infoDialogLoader.active = true
            }

            Item { Layout.fillWidth: true }

            Label {
                visible: webView.loading
                text: loginManager.status
                font.bold: true
                verticalAlignment: Label.AlignVCenter
            }

            BusyIndicator {
                Material.accent: Material.color(Material.Red, Material.Shade500)
                implicitHeight: parent.height
                visible: webView.loading
                running: webView.loading
            }
        }
    }

    LoginManager {
        id: loginManager
        webView: webView
        onLoginRequested: donator.disconnect()
        onSuccessfullyLoggedIn: donator.prepareForDonations()
    }

    DonationManager {
        id: donator
        webView: webView
        cnpj: !isFirstRun ? entityCnpj : ''
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

            function onLoginRequested(user, ssn, password) {
                loginManager.login(user, ssn, password)
            }
        }
    }

    Loader {
        id: settingsDialogLoader
        source: 'SettingsDialog.qml'
        active: false

        Connections {
            target: settingsDialogLoader.item

            function onClosing() {
                settingsDialogLoader.active = false
            }
        }
    }

    Loader {
        id: infoDialogLoader
        source: 'InfoDialog.qml'
        active: false

        Connections {
            target: settingsDialogLoader.item

            function onClosing() {
                settingsDialogLoader.active = false
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        TextField {
            Layout.fillWidth: true
            Layout.topMargin: 5
            placeholderText: 'Chave de Acesso'
            inputMask: '99999999999999999999999999999999999999999999'
            focus: true
            onTextChanged: {
                if (text.length === 44) {
                    donator.addAccessKey(text)
                    clear()
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            visible: loginManager.hasLoginErrors
            implicitHeight: children[0].implicitHeight
            color: '#2C0B0E'
            border.width: 1
            border.color: '#842029'
            radius: 5

            Text {
                anchors.fill: parent
                padding: 10
                wrapMode: Text.Wrap
                color: '#EA868F'
                text: '<b>CPF ou Senha Inválidos</b><br>Recomenda-se remover o usuário e cadastra-lo novamente com as informações corretas.'
                font.pixelSize: 16
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        WebEngineView {
            id: webView
            Layout.fillWidth: true
            Layout.fillHeight: true
            enabled: false
            Component.onCompleted: {
                if (isFirstRun) {
                    url = Qt.url('https://www.google.com'); // TODO: Change this to a instructions page stored in the resources
                }
            }
        }
    }
}
