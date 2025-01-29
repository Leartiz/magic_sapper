import QtQuick
import QtQuick.Controls

import "../Widgets"
import "../Resources"

Column {
    id: root
    width: _slider.implicitWidth
    spacing: 5

    property alias basicSlider: _slider
    property alias basicBgSlider: _rectBg

    signal zoomChanged(double val)

    ZoomBtn {
        id: _btnZoomIn
        anchors.left: parent.left
        anchors.right: parent.right

        imgSource: ResourcesProvider.imgIosBZoomIn
        onClicked: _slider.increase()
    }

    Slider {
        id: _slider
        orientation: Qt.Vertical

        stepSize: 0.05
        value: 0.75
        from: 0.1
        to: 3.0

        background: Rectangle {
            id: _rectBg
            x: _slider.leftPadding + _slider.availableWidth / 2 - width / 2
            y: _slider.topPadding
            implicitWidth: 6
            implicitHeight: 150
            width: implicitWidth
            height: _slider.availableHeight
            radius: 2
            color: "#616161"

            Rectangle {
                width: parent.width - 1
                height: _slider.visualPosition * parent.height
                color: "#B6B6B7"
                radius: 2
            }
        }

        handle: Rectangle {
            id: _rectHandle
            implicitWidth: 35
            implicitHeight: 35
            x: _slider.leftPadding + _slider.availableWidth / 2 - _rectHandle.width / 2
            y: _slider.topPadding + _slider.visualPosition * (_slider.availableHeight - _rectHandle.height)
            radius: 3
            color: _slider.pressed ? "#616161" : "#B6B6B7"
            border.color: _slider.pressed ? "#B6B6B7" : "#616161"
            border.width: 2
        }

        Connections {
            function onValueChanged() {
                root.zoomChanged(_slider.value);
            }
        }
    }

    ZoomBtn {
        id: _btnZoomOut
        anchors.left: parent.left
        anchors.right: parent.right

        imgSource: ResourcesProvider.imgIosBZoomOut
        onClicked: _slider.decrease()
    }
}


