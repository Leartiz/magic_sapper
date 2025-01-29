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

    background: Rectangle {
        id: _rectBg
        color: "#606060"
        radius: 9
    }

    signal clicked()

    MouseArea {
        id: _maBtnTopBar
        anchors.fill: parent

        Connections {
            function onClicked() {
                root.clicked();
            }
            function onPressed() {
                _rectBg.color = Qt.lighter("#606060", 1.35);
            }
            function onReleased() {
                _rectBg.color = "#606060";
            }
        }
    }
}
