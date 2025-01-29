import QtQuick

Rectangle {
    id: root
    height: root.width

    radius: 3
    color: _maZoom.pressed ? "#616161" : "#B6B6B7"

    border.width: 2
    border.color: _maZoom.pressed ? "#B6B6B7" : "#616161"

    property alias imgSource: _imgZoom.source
    signal clicked()

    Image {
        id: _imgZoom
        anchors.fill: parent
        anchors.margins: 5
        fillMode: Image.PreserveAspectFit
    }

    MouseArea {
        id: _maZoom
        anchors.fill: parent

        onClicked: root.clicked()
    }
}
