import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    title: 'Informações | AutoNota'
    width: 320
    height: 150
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    modality: Qt.ApplicationModal

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        Label {
            Layout.fillWidth: true
            text: 'AutoNota'
            font.pixelSize: 35
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            Layout.fillWidth: true
            text: 'Versão 1.0.0'
            horizontalAlignment: Text.AlignHCenter
        }

        Item { Layout.fillHeight: true }

        Label {
            Layout.fillWidth: true
            font.pixelSize: 18
            text: 'Desenvolvido por: <a href="https://github.com/erickruhcardozo">Erick Ruh Cardozo</a>'
            horizontalAlignment: Text.AlignHCenter
            onLinkActivated: (link) => Qt.openUrlExternally(link)
        }

        Item { Layout.fillHeight: true }
    }
}
