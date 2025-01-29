import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: _lblModeNme.implicitWidth
    height: 50

    property alias lblModeNme: _lblModeNme
    property alias recSeld: _recSeld

    signal clicked()

    Label {
        id: _lblModeNme
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: _recSeld.top
        leftPadding: 25
        rightPadding: 25
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 17 // more!
        color: "white"
    }

    Rectangle {
        id: _recSeld
        height: 3
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "transparent"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
