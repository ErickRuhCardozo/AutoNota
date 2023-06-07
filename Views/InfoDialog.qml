import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    title: 'Informações | AutoNota'
    width: 320
    height: 180
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    modality: Qt.ApplicationModal

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        Image {
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 5
            source: 'qrc:/Icons/app.svg'
            smooth: true
            antialiasing: true
            sourceSize: Qt.size(50, 50)
        }

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
    }
}
