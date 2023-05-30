import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import AutoNota

ApplicationWindow {
    id: dialog
    visible: true
    modality: Qt.ApplicationModal
    width: 500

    SettingsManager {
        id: settings
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 5
        columns: 2

        Label { text: 'Usuário Padrão:' }
        ComboBox {
            Layout.fillWidth: true
            textRole: 'name'
            valueRole: 'id'
            currentIndex: -1
            model: UsersItemModel { }
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
                    dialog.close()
                }
            }
        }
    }
}
