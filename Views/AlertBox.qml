import QtQuick

Rectangle {
    property string message: ''

    implicitWidth: parent.width
    implicitHeight: text.implicitHeight
    color: '#2C0B0E'
    border.width: 1
    border.color: '#842029'
    radius: 5

    Text {
        id: text
        anchors.fill: parent
        padding: 10
        wrapMode: Text.Wrap
        color: '#EA868F'
        text: parent.message
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
