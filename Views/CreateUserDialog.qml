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
    title: 'Criar Novo Usuário'

    property var usersModel: undefined
    property bool canSave: nameField.acceptableInput && ssnField.acceptableInput && passwordField.acceptableInput

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
            validator: RegularExpressionValidator { regularExpression: /[\w\s]{3,10}/ }
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
            visible: false
            Layout.columnSpan: 2
            Layout.fillWidth: true
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            color: 'red'
            text: 'Preencha todos os campos corretamente, por favor.'
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
                    if (dialog.canSave) {
                        usersModel.addUser(nameField.text, ssnField.text, passwordField.text)
                        usersModel.saveUsers()
                        dialog.close()
                    } else {
                        errorText.visible = true
                    }
                }
            }
        }
    }
}
