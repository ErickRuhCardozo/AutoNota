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
    Component.onCompleted: {
        if (defaultSsn !== '') {
            loginManager.login(defaultSsn, defaultPassword)
        }
    }

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

            ToolButton {
                focusPolicy: Qt.NoFocus
                icon.source: 'qrc:/Assets/Icons/gear.svg'
                ToolTip.visible: hovered
                ToolTip.text: 'Configurações'
                onClicked: settingsDialogLoader.active = true
            }

            Item { Layout.fillWidth: true }

            BusyIndicator {
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
        onSuccessfullyLoggedIn: donator.prepareForDonations()
        onLoginRequested: donator.disconnect()
    }

    DonationManager {
        id: donator
        webView: webView
        cnpj: entityCnpj
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

        AlertBox {
            visible: loginManager.hasLoginErrors
            message: '<b>CPF ou Senha Inválidos</b><br>Recomenda-se remover o usuário e cadastra-lo novamente com as informações corretas.'
        }

        WebEngineView {
            id: webView
            Layout.fillWidth: true
            Layout.fillHeight: true
            enabled: false
        }
    }
}
