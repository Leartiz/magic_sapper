import QtQuick
import QtQuick.Controls

import Qt5Compat.GraphicalEffects

ToolBar {
    id: root
    width: 480
    height: 50

    property alias pIndCount: _pIndicator.count
    property alias pIndCurrentIndex: _pIndicator.currentIndex

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
            verticalOffset: -2
            radius: 8
            samples: 17
            color: "#80000000"
        }
    }

    PageIndicator {
        id: _pIndicator
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        interactive: false

        delegate: Rectangle {
            implicitWidth: 8
            implicitHeight: 8
            radius: width / 2

            color: "white"
            opacity: index === _pIndicator.currentIndex ? 1 : 0.35;

            Behavior on opacity {
                OpacityAnimator {
                    duration: 100
                }
            }
        }
    }
}
