import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import AutoNota

Window {
    width: 400
    visible: true
    modality: Qt.ApplicationModal
    title: 'Usuários Cadastrados'

    UsersItemModel { id: usersModel }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        HorizontalHeaderView {
            syncView: tableView
        }

        TableView {
            id: tableView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: usersModel
            columnWidthProvider: () => tableView.width / model.columnCount()
            clip: true
            delegate: RowLayout {
                CheckBox {
                    visible: model.column === 0
                    checked: model['checked']
                }

                Text {
                    horizontalAlignment: Text.AlignHCenter
                    text: {
                        switch (model.column) {
                            case 0: return model['name']
                            case 1: return model['ssn']
                            case 2: return model['password']
                        }
                    }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Button {
                text: 'Cadastrar Usuário'
                onClicked: {
                    const component = Qt.createComponent('CreateUserDialog.qml')
                    const dialog = component.createObject(this, { usersModel: usersModel })
                    dialog.show()
                }
            }

            Button {
                text: 'Remover Usuários Marcados'
                onClicked: {
                    for (let i = 0; i < usersModel.rowCount(); i++) {
                        console.log(usersModel.data(usersModel.index(i, 0), UsersModel.CheckedRole))
                    }
                }
            }
        }
    }
}
