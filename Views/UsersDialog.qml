/*
 * Author: Erick Ruh Cardozo (https://github.com/erickruhcardozo)
 * Date: May 19, 2023 - 2:30 PM
 */

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import AutoNota

ApplicationWindow {
    signal loginRequested(string user, string ssn, string password)

    id: dialog
    width: 500
    height: 350
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    visible: true
    modality: Qt.ApplicationModal
    title: 'Usuários Cadastrados | AutoNota'
    header: ToolBar {
        RowLayout {
            ToolButton {
                icon.source: 'qrc:/Icons/user-plus.svg'
                ToolTip.visible: hovered
                ToolTip.text: 'Adicionar Usuário'
                onClicked: {
                    const component = Qt.createComponent('CreateUserDialog.qml')
                    const dialog = component.createObject(this, { usersModel: usersModel })
                    dialog.show()
                }
            }

            ToolButton {
                icon.source: 'qrc:/Icons/user-minus.svg'
                ToolTip.visible: hovered
                ToolTip.text: 'Remover Usuário Selecionado'
                enabled: selectionModel.hasSelection
                onClicked: {
                    const row = selectionModel.selectedIndexes[0].row
                    usersModel.removeRows(row, 0)
                }
            }

            ToolButton {
                icon.source: 'qrc:/Icons/user-login.svg'
                ToolTip.visible: hovered
                ToolTip.text: 'Logar Com Usuário Selecionado'
                enabled: selectionModel.hasSelection
                onClicked: {
                    const index = selectionModel.selectedIndexes[0]
                    const user = usersModel.data(index, UsersItemModel.ObjectRole)
                    dialog.loginRequested(user.fullName, user.ssn, user.password)
                    dialog.close()
                }
            }
        }
    }

    UsersItemModel { id: usersModel }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        HorizontalHeaderView { syncView: tableView }

        TableView {
            id: tableView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: usersModel
            columnWidthProvider: () => tableView.width / model.columnCount()
            clip: true
            selectionBehavior: TableView.SelectRows
            selectionModel: ItemSelectionModel { id: selectionModel; model: usersModel }

            delegate: ItemDelegate {
                required property int row
                required property bool selected
                highlighted: selected
                text: {
                    switch (model.column) {
                        case 0: return model['name']
                        case 1: return model['ssn']
                        case 2: return model['password']
                    }
                }

                onClicked: {
                    selectionModel.clearSelection()

                    for (let i = 0; i < 3; i++) {
                        const index = usersModel.index(row, i)
                        selectionModel.select(index, ItemSelectionModel.Select)
                    }
                }
            }
        }
    }
}
