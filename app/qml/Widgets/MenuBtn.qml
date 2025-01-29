import QtQuick
import QtQuick.Controls

import Qt5Compat.GraphicalEffects

Button {
    id: root
    width: 400
    height: _lblMode.implicitHeight + _lblSizes.implicitHeight

    background: Rectangle {
        color: root.pressed ? Qt.lighter("#616161", 1.15) : "#616161"
        radius: 3
        border.width: 2
        border.color: "#363636"
    }

    property alias lblModeText: _lblMode.text
    property alias lblSizesText: _lblSizes.text
    property alias imageCurMode: _imageCurMode

    Label {
        id: _lblMode
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.verticalCenter
        padding: 3

        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter

        elide: Label.ElideRight
        font.pointSize: 22
        color: "white"
    }

    Label {
        id: _lblSizes
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.verticalCenter
        anchors.bottom: parent.bottom
        topPadding: 3
        bottomPadding: 3
        rightPadding: 28
        leftPadding: 3
        verticalAlignment: Label.AlignVCenter
        horizontalAlignment: Label.AlignRight
        elide: Label.ElideRight
        font.pointSize: 18
        color: "white"
    }

    Image {
        id: _imageCurMode
        width: _imageCurMode.height
        height: root.height / 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        z: 10
        anchors.leftMargin: 10
        fillMode: Image.PreserveAspectFit
    }

    DropShadow {
        anchors.fill: _imageCurMode
        source: _imageCurMode
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8.0
        samples: 17
        color: "#80000000"
    }
}
