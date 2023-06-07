/*
 * Author: Erick Ruh Cardozo (https://github.com/erickruhcardozo)
 * Date: May 17, 2023 - 2:22 PM
 */

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import AutoNota

ApplicationWindow {
    id: dialog
    width: 400
    height: 225
    visible: true
    modality: Qt.ApplicationModal
    title: 'Criar Novo Usuário | AutoNota'

    property var usersModel: undefined

    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.margins: 10
        columns: 2

        Label { text: 'Nome:' }
        TextField {
            id: nameField
            focus: true
            Layout.fillWidth: true
            validator: RegularExpressionValidator { regularExpression: /[\w\s]{3,30}/ }
        }

        Label { text: 'CPF:' }
        TextField {
            id: ssnField
            Layout.fillWidth: true
            inputMask: '999\.999\.999\-99'
        }

        Label { text: 'Senha:' }
        TextField {
            id: passwordField
            Layout.fillWidth: true
            validator: RegularExpressionValidator { regularExpression: /.+/ }
        }

        Text {
            id: errorText
            visible: true
            Layout.columnSpan: 2
            Layout.fillWidth: true
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            color: 'red'
            text: usersModel.error
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.columnSpan: 2

            Button {
                Layout.fillWidth: true
                text: 'Cancelar'
                onClicked: dialog.close()
            }

            Item { Layout.fillWidth: true }

            Button {
                Layout.fillWidth: true
                text: 'Cadastrar'

                onClicked: {
                    if (nameField.acceptableInput && ssnField.acceptableInput && passwordField.acceptableInput) {
                        usersModel.addUser(nameField.text, ssnField.text, passwordField.text)

                        if (usersModel.error === '') {
                            dialog.close()
                        }
                    }
                }
            }
        }
    }
}
