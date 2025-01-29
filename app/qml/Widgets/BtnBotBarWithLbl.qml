import QtQuick
import QtQuick.Controls

Item {
    id:root
    width: root.height + _lbl.implicitWidth
    height: 50

    readonly property alias presd: _ma.pressed
    property alias contentItem: _btn.contentItem
    property alias rectBg: _rectBg
    signal clicked()

    Control {
        id: _btn
        width: _btn.height

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        topInset: 3
        bottomInset: 3
        leftInset: 3
        rightInset: 3

        padding: 5

        background: Rectangle {
            id: _rectBg
            color: "#606060" // default!
            radius: 17
        }

        MouseArea {
            id: _ma
            anchors.fill: parent

            Connections {
                function onClicked() {
                    root.clicked()
                }
            }
        }
    }

    property alias lblText: _lbl.text
    Label {
        id: _lbl
        anchors.left: _btn.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        rightPadding: 5
        leftPadding: 5

        font.pointSize: 22
        color: "white"
        text: qsTr("N")
    }
}


