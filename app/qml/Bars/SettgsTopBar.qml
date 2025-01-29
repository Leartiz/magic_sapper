import QtQuick
import QtQuick.Controls

import Qt5Compat.GraphicalEffects

import "../Resources"
import "../Widgets"

ToolBar {
    id: root
    width: 480
    height: 50

    background: Item {
        id: _itemBg

        Rectangle {
            id: _rectBg
            anchors.top: _itemBg.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height
            color: "#606060"
        }

        DropShadow {
            anchors.fill: _rectBg
            source: _rectBg
            horizontalOffset: 0
            verticalOffset: 4
            radius: 8
            samples: 17
            color: "#80000000"
        }
    }

    signal btnBackClicked()
    BtnTopBar {
        id: _btnBack
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        contentItem: Image {
            id: _imgBack

            fillMode: Image.PreserveAspectFit
            source: ResourcesProvider.imgIosWBack
        }

        Connections {
            target: _btnBack
            function onClicked() {
                root.btnBackClicked();
            }
        }
    }

    Image {
        id: _imgSettgs
        width: _imgSettgs.height
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 3
        anchors.horizontalCenter: parent.horizontalCenter
        source: ResourcesProvider.imgIosWSettings
        fillMode: Image.PreserveAspectFit
    }
}
