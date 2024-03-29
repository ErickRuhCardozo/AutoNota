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
    id: window
    width: 800
    height: 450
    visible: true
    title: 'AutoNota | Desenvolvido por Erick Ruh Cardozo'
    Component.onCompleted: {
        // Context Properties defined in main.cpp
        if (entityCnpj === '') {
            settingsDialogLoader.active = true;
        }

        if (defaultUser !== '' && defaultSsn !== '' && defaultPassword !== '') {
            loginManager.login(defaultUser, defaultSsn, defaultPassword)
        }
    }

    header: ToolBar {
        implicitHeight: 40

        RowLayout {
            anchors.fill: parent

            ToolButton {
                focusPolicy: Qt.NoFocus
                icon.source: 'qrc:/Icons/users.svg'
                icon.height: 18
                icon.width: 18
                ToolTip.visible: hovered
                ToolTip.text: 'Usuários'
                onClicked: usersDialogLoader.active = true
            }

            ToolButton {
                focusPolicy: Qt.NoFocus
                icon.source: 'qrc:/Icons/gear.svg'
                icon.width: 18
                icon.height: 18
                ToolTip.visible: hovered
                ToolTip.text: 'Configurações'
                onClicked: settingsDialogLoader.active = true
            }

            ToolButton {
                focusPolicy: Qt.NoFocus
                icon.source: 'qrc:/Icons/info.svg'
                icon.width: 18
                icon.height: 18
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

    footer: ToolBar {
        implicitHeight: 20

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 8
            anchors.rightMargin: 8

            Label { text: 'Escaneadas: ' }
            Label { text: donationManager.scanned }

            Item { Layout.fillWidth: true }

            Label { text: 'Doadas: ' }
            Label { text: donationManager.donated }

            Item { Layout.fillWidth: true }

            Label { text: 'Rejeitadas: ' }
            Label { text: donationManager.rejected }
        }
    }

    LoginManager {
        id: loginManager
        webView: webView
        onLoginRequested: donationManager.disconnect()
        onSuccessfullyLoggedIn: donationManager.prepareForDonations()
    }

    DonationManager {
        id: donationManager
        webView: webView
        cnpj: entityCnpj // Context Property defined in main.cpp
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

            function onAboutToClose(cnpj) {
                entityCnpj = cnpj
                donationManager.cnpj = cnpj
            }

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

    Timer {
        interval: 3000
        running: true
        repeat: true
        onTriggered: !accessKeyField.focus && accessKeyField.forceActiveFocus()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        TextField {
            id: accessKeyField
            Layout.fillWidth: true
            Layout.topMargin: 5
            focus: true
            placeholderText: 'Chave de Acesso'
            KeyNavigation.tab: accessKeyField
            KeyNavigation.backtab: accessKeyField
            onCursorPositionChanged: accessKeyField.cursorPosition = accessKeyField.text.length
            onEditingFinished: {
                let regex = /(?:p=)?(\d{44})/;

                if (regex.test(accessKeyField.text)) {
                    let accessKey = text.match(regex)[1]
                    donationManager.addAccessKey(accessKey)
                }

                accessKeyField.clear()
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
            url: Qt.url('qrc:/index.html')
        }
    }
}
