import QtQuick
import QtQuick.Controls

Control {
    id: root
    width: root.height

    topInset: 3
    bottomInset: 3
    leftInset: 3
    rightInset: 3

    padding: 5

    property alias rectBg: _rectBg
    background: Rectangle {
        id: _rectBg
        color: "#606060" // default!
        radius: 17
    }

    readonly property alias presd: _ma.pressed
    signal clicked()

    MouseArea {
        id: _ma
        anchors.fill: parent

        Connections {
            function onClicked() {
                root.clicked();
            }
        }
    }
}
