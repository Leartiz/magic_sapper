import QtQuick
import QtQuick.Controls

Slider {
    id: root
    width: root.width / 3
    anchors.top: parent.top
    anchors.left: _sliderRows.right
    anchors.bottom: _lblCols.top
    orientation: Qt.Vertical

    value: 0.5

    background: Rectangle {
        x: root.leftPadding + root.availableWidth / 2 - width / 2
        y: root.topPadding
        width: implicitWidth
        height: root.availableHeight
        implicitWidth: 6
        implicitHeight: 150
        color: "#353637"
        radius: 5

        Rectangle {
            width: parent.width
            height: root.visualPosition * parent.height
            color: Qt.lighter("#616161", 1.05)
            radius: 5
        }
    }
}
