import QtQuick
import QtQuick.Controls

import Qt5Compat.GraphicalEffects

Rectangle {
    id: root
    width: 250
    height: 250

    color: "#303b37"
    border.width: 1
    border.color: Qt.lighter("#303B37", 1.25)

    property alias imgMainStateSrc: _imgMainState.source
    property alias imgExtraStateSrc: _imgExtraState.source
    property alias isVisibleCntnt: _rectContent.visible

    Rectangle {
        id: _rectEmpty
        radius: 5
        anchors.fill: parent
        anchors.margins: 3
        color: "#14201C"
        visible: !root.isVisibleCntnt
    }

    Rectangle {
        id: _rectContent
        radius: 5
        anchors.fill: parent
        anchors.margins: 3
        visible: root.isVisibleCntnt

        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#6c800c"
            }

            GradientStop {
                position: 0.75
                color: Qt.darker("#6c800c", 1.75)
            }
        }
    }

    Image {
        id: _imgMainState
        anchors.fill: parent
        anchors.margins: 6
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: _imgExtraState
        anchors.fill: parent
        anchors.margins: 6
        opacity: 0.75
        fillMode: Image.PreserveAspectFit
    }
}
