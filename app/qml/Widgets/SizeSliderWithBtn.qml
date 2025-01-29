import QtQuick 2.12
import QtQuick.Controls 2.12

import "../Resources"

Item {
    id: root

    width: _recBtnSH.width + root.offsetForHide
    height: _sizeSlider.implicitHeight // column!
    anchors.rightMargin: -root.offsetForHide

    // fwd!
    property alias sizeSlider: _sizeSlider
    property alias basicSlider: _sizeSlider.basicSlider
    property alias basicBgSlider: _sizeSlider.basicBgSlider

    property real offsetForShow: 5
    property real offsetForHide: _sizeSlider.implicitWidth + _recBtnSH.anchors.rightMargin

    signal zoomChanged(double val)

    SizeSlider {
        id: _sizeSlider
        z: 35
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        Connections {
            target: _sizeSlider
            function onZoomChanged(val) {
                root.zoomChanged(val);
            }
        }
    }

    signal clickedBtnSH()
    Rectangle {
        id: _recBtnSH
        z: 30
        width: 25
        height: 50
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: _sizeSlider.left
        anchors.rightMargin: 3

        radius: 25
        color: _maBtnSH.pressed ? "#616161" : "#B6B6B7"

        border.width: 2
        border.color: _maBtnSH.pressed ? "#B6B6B7" : "#616161"

        Rectangle {
            id: _recBtnSH1
            anchors.left: parent.horizontalCenter
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            color: _maBtnSH.pressed ? "#616161" : "#B6B6B7"
            radius: 0
            border.width: _recBtnSH.border.width
            border.color: _maBtnSH.pressed ? "#B6B6B7" : "#616161"
        }

        Rectangle {
            id: _recBtnSH2
            anchors.left: parent.horizontalCenter
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.rightMargin: _recBtnSH.border.width
            anchors.bottomMargin: _recBtnSH.border.width
            anchors.topMargin: _recBtnSH.border.width
            color: _maBtnSH.pressed ? "#616161" : "#B6B6B7"
        }

        Image {
            id: _imgArrow
            anchors.fill: parent
            anchors.margins: _recBtnSH.border.width
            fillMode: Image.PreserveAspectFit
            source: ResourcesProvider.imgGnBChevronLeft

            // axis!
            transform: [
                Rotation {
                    id: _rotImgArrow
                    origin {
                        x: _imgArrow.width / 2
                        y: _imgArrow.height / 2
                    }
                    axis {
                        x: 0
                        y: 1
                        z: 0
                    }
                }
            ]
        }

        MouseArea {
            id: _maBtnSH
            enabled: interactiveBtnSH
            anchors.fill: parent

            onClicked: root.clickedBtnSH()
        }

    }

    property bool interactiveBtnSH: true
    property bool autoShowHide: true

    Connections {
        target: root
        function onClickedBtnSH() {
            if (!root.autoShowHide) return;

            if (root.showed) {
                root.hideSizeSlider();
                return;
            }
            showSizeSlider();
        }
    }

    property bool showed: false
    function showSizeSlider() {
        _parAnimShow.start();
    }
    function hideSizeSlider() {
        _parAnimHide.start();
    }

    property real numAnimDuration: 100
    ParallelAnimation {
        id: _parAnimShow
        NumberAnimation {
            target: _rotImgArrow
            properties: "angle"
            to: 180
            duration: root.numAnimDuration
        }
        NumberAnimation {
            target: root
            properties: "anchors.rightMargin"
            to: root.offsetForShow
            duration: root.numAnimDuration
        }
        NumberAnimation {
            target: _recBtnSH
            properties: "width"
            to: 35 // more!
            duration: root.numAnimDuration
        }

        onStarted: root.enabled = false
        onFinished: root.enabled = root.showed = true
    }
    ParallelAnimation {
        id: _parAnimHide
        NumberAnimation {
            target: _rotImgArrow
            properties: "angle"
            to: 0
            duration: root.numAnimDuration
        }
        NumberAnimation {
            target: root
            properties: "anchors.rightMargin"
            to: -root.offsetForHide
            duration: root.numAnimDuration
        }
        NumberAnimation {
            target: _recBtnSH
            properties: "width"
            to: 25
            duration: root.numAnimDuration
        }

        onStarted: root.enabled = false
        onFinished: root.enabled = !(root.showed = false)
    }
}
