import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import AutoNota

ApplicationWindow {
    id: dialog
    visible: true
    modality: Qt.ApplicationModal
    width: 500

    SettingsManager { id: settings }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 5
        columns: 2

        Label { text: 'Usuário Padrão:' }
        RowLayout {
            ComboBox {
                id: userCombo
                Layout.fillWidth: true
                textRole: 'name'
                valueRole: 'id'
                model: UsersItemModel { }
                Component.onCompleted: currentIndex = indexOfValue(settings.defaultUser)
            }

            ToolButton {
                icon.source: 'qrc:/Icons/undo.svg'
                onClicked: userCombo.currentIndex = -1
            }
        }

        Label { text: 'CNPJ:'; Layout.alignment: Qt.AlignRight }
        TextField {
            id: cnpjField
            Layout.fillWidth: true
            inputMask: '99.999.999/9999-99'
            text: settings.cnpj
        }

        RowLayout {
            Layout.columnSpan: 2
            Layout.fillWidth: true

            Button {
                Layout.fillWidth: true
                text: 'Cancelar'
                onClicked: dialog.close()
            }

            Button {
                Layout.fillWidth: true
                text: ' Salvar '
                onClicked: {
                    settings.cnpj = cnpjField.text
                    settings.defaultUser = userCombo.currentValue ?? 0
                    dialog.close()
                }
            }
        }
    }
}
