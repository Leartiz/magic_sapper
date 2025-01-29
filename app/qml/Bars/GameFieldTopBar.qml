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

    property alias imgNewGame: _imgNewGame

    signal btnSettingsClicked()
    signal btnLBClicked()
    signal btnNewGameClicked()

    BtnTopBar {
        id: _btnSettings
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        contentItem: Image {
            id: _imgSettings

            fillMode: Image.PreserveAspectFit
            source: ResourcesProvider.imgIosWSettings

            transform: [
                Rotation {
                    id: _rotImgSettings
                    origin {
                        x: _imgSettings.width / 2
                        y: _imgSettings.height / 2
                    }

                    Behavior on angle {
                        NumberAnimation {
                            duration: 250
                        }
                    }
                }
            ]
        }

        Connections {
            target: _btnSettings
            function onClicked() {
                _btnSettings.applyAnim();
                root.btnSettingsClicked();
            }
        }

        function applyAnim() {
            if (_rotImgSettings.angle === 25) {
                _rotImgSettings.angle = 0;
                return;
            }
            _rotImgSettings.angle = 25;
        }
    }

    BtnTopBar {
        id: _btnLB
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        contentItem: Image {
            id: _imgLB

            fillMode: Image.PreserveAspectFit
            source: ResourcesProvider.imgIosWLeaderboard

            transform: [
                Scale {
                    id: _scaleImgLB
                    origin.x: _imgLB.width / 2
                    origin.y: _imgLB.height / 2

                    Behavior on xScale {
                        NumberAnimation {
                            duration: 125
                        }
                    }
                    Behavior on yScale {
                        NumberAnimation {
                            duration: 175
                        }
                    }
                }
            ]
        }

        Connections {
            target: _btnLB
            function onClicked() {
                _btnLB.applyAnim();
                root.btnLBClicked();
            }
        }

        function applyAnim() {
            if (_scaleImgLB.xScale === 0.9) {
                _scaleImgLB.xScale = _scaleImgLB.yScale = 1;
                return;
            }
            _scaleImgLB.xScale = 0.9;
            _scaleImgLB.yScale = 1.1;
        }
    }

    BtnTopBar {
        id: _btnNewGame
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        contentItem: Image {
            id: _imgNewGame

            fillMode: Image.PreserveAspectFit
            source: ResourcesProvider.imgSmilesSmileSt0

            transform: [
                Rotation {
                    id: _rotImgNewGame
                    origin.x: _imgNewGame.width / 2
                    origin.y: _imgNewGame.height / 2

                    axis {
                        x: 1
                        y: 0
                        z: 0
                    }

                    Behavior on angle {
                        NumberAnimation {
                            duration: 250
                        }
                    }
                }
            ]
        }

        Connections {
            target: _btnNewGame
            function onClicked() {
                _btnNewGame.applyAnim();
                root.btnNewGameClicked();
            }
        }

        function applyAnim() {
            if (_rotImgNewGame.angle === 360) {
                _rotImgNewGame.angle = 0;
                return;
            }
            _rotImgNewGame.angle = 360;
        }
    }

    property alias labelBomb: _lblBomb.text
    property alias labelTime: _lblTime.text

    Label {
        id: _lblBomb
        anchors.left: _btnLB.right
        anchors.right: _btnNewGame.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 22
        color: "white"
        text: qsTr("BOMB")
    }

    Label {
        id: _lblTime
        anchors.left: _btnNewGame.right
        anchors.right: _btnSettings.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 22
        color: "white"
        text: qsTr("TIME")
    }
}
