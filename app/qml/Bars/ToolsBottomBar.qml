import QtQuick
import QtQuick.Controls

import Qt5Compat.GraphicalEffects

import "../Resources"
import "../Widgets"

import WrTool 1.0

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
            verticalOffset: -2
            radius: 8
            samples: 17
            color: "#80000000"
        }
    }

    property alias btnQuestion: _btnQuestion
    property alias numAvblPromt: _btnPrompt.lblText

    signal btnPromptClicked()
    BtnBotBarWithLbl {
        id: _btnPrompt
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        rectBg.color: _btnPrompt.presd ? Qt.lighter("#606060", 1.35) : "#606060"
        contentItem: Image {
            id: _imgPrompt
            fillMode: Image.PreserveAspectFit
            source: ResourcesProvider.imgCcCrPrompt

            transform: [
                Rotation {
                    id: _rotImgPrompt
                    origin.x: _imgPrompt.width / 2
                    origin.y: _imgPrompt.height / 2

                    axis {
                        x: 0
                        y: 1
                        z: 0
                    }

                    Behavior on angle {
                        NumberAnimation {
                            duration: 225
                        }
                    }
                }
            ]
        }

        Connections {
            function onClicked() {                
                _btnPrompt.applyAnim();
                root.btnPromptClicked();
            }
        }

        function applyAnim() {
            if (_rotImgPrompt.angle === 180) {
                _rotImgPrompt.angle = 0;
                return;
            }
            _rotImgPrompt.angle = 180;
        }
    }

    // public!
    function setShvl() {
        _privPropsState.btnSt = _privPropsState.shvlSt;
        _btnShvl.applyAnim();
    }
    function setFlag() {
        _privPropsState.btnSt = _privPropsState.flagSt;
        _btnFlag.applyAnim();
    }
    signal toolSelected(int tool)
    Item {
        id: _itemPartBotBar
        clip: true

        anchors.left: _btnPrompt.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        QtObject {
            id: _privPropsState
            property int btnSt: _privPropsState.shvlSt
            onBtnStChanged: root.toolSelected(_privPropsState.btnSt)

            // const!
            readonly property int shvlSt: WrTool.Shovel
            readonly property int flagSt: WrTool.Flag
            readonly property int questionSt: WrTool.Question
            readonly property int msSt: WrTool.Magic_stick
        }

        Row {
            id: row
            spacing: 5

            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            BtnBotBar {
                id: _btnShvl
                width: _btnShvl.height

                anchors.top: parent.top
                anchors.bottom: parent.bottom

                rectBg.color: _privPropsState.btnSt === _privPropsState.shvlSt ? Qt.lighter("#606060", 1.55) : "#606060"
                contentItem: Image {
                    id: _imgShvl
                    fillMode: Image.PreserveAspectFit
                    source: ResourcesProvider.imgCcCrShovel
                }

                Connections {
                    function onClicked() {
                        _privPropsState.btnSt = _privPropsState.shvlSt;
                        _btnShvl.applyAnim();
                    }
                }

                function applyAnim() {
                    _seqAnimShvl.start();
                }

                SequentialAnimation {
                    id: _seqAnimShvl
                    NumberAnimation {
                        target: _imgShvl
                        properties: "rotation"
                        to: -40
                        duration: 125
                    }
                    NumberAnimation {
                        target: _imgShvl
                        properties: "rotation"
                        to: 0
                        duration: 125
                    }
                }
            }

            BtnBotBar {
                id: _btnFlag
                width: _btnFlag.height

                anchors.top: parent.top
                anchors.bottom: parent.bottom

                rectBg.color: _privPropsState.btnSt === _privPropsState.flagSt ? Qt.lighter("#606060", 1.55) : "#606060"
                contentItem: Image {
                    id: _imgFlag
                    fillMode: Image.PreserveAspectFit
                    source: ResourcesProvider.imgCcCrFlag

                    transform: Scale {
                        id: _scaleImgFlag
                        origin.x: 0
                        origin.y: _imgFlag.height / 2
                    }
                }

                Connections {
                    function onClicked() {
                        _privPropsState.btnSt = _privPropsState.flagSt;
                        _btnFlag.applyAnim();
                    }
                }

                function applyAnim() {
                    _seqAnimFlag.start();
                }

                SequentialAnimation {
                    id: _seqAnimFlag
                    NumberAnimation {
                        target: _scaleImgFlag
                        properties: "xScale"
                        to: 1.2
                        duration: 125
                    }
                    NumberAnimation {
                        target: _scaleImgFlag
                        properties: "xScale"
                        to: 1
                        duration: 125
                    }
                }
            }

            BtnBotBar {
                id: _btnQuestion
                width: _btnQuestion.height

                anchors.top: parent.top
                anchors.bottom: parent.bottom

                rectBg.color: _privPropsState.btnSt === _privPropsState.questionSt ? Qt.lighter("#606060", 1.55) : "#606060"
                contentItem: Image {
                    id: _imgQuestion
                    fillMode: Image.PreserveAspectFit
                    source: ResourcesProvider.imgCcCrQuestion

                    transform: Scale {
                        id: _scaleImgQuestion
                        origin.x: _imgQuestion.width / 2
                        origin.y: _imgQuestion.height / 2
                    }
                }

                Connections {
                    function onClicked() {
                        _privPropsState.btnSt = _privPropsState.questionSt;
                        _btnQuestion.applyAnim();
                    }
                }

                readonly property string stDefault: "_default"
                readonly property string stHidden: "_hidden"

                states: [
                    State {
                        name: _btnQuestion.stDefault
                        PropertyChanges {
                            target: _btnQuestion
                            visible: true
                            width: _btnQuestion.height
                        }
                    },
                    State {
                        name: _btnQuestion.stHidden
                        PropertyChanges {
                            target: _btnQuestion
                            visible: false
                            width: 0
                        }
                    }
                ]

                function applyAnim() {
                    _seqAnimQuestion.start();
                }

                SequentialAnimation {
                    id: _seqAnimQuestion
                    NumberAnimation {
                        target: _scaleImgQuestion
                        properties: "xScale, yScale"
                        to: 1.2
                        duration: 150
                    }
                    NumberAnimation {
                        target: _scaleImgQuestion
                        properties: "xScale, yScale"
                        to: 1
                        duration: 100
                    }
                }
            }

            BtnBotBar {
                id: _btnMs
                width: _btnMs.height

                anchors.top: parent.top
                anchors.bottom: parent.bottom

                rectBg.color: _privPropsState.btnSt === _privPropsState.msSt ? Qt.lighter("#606060", 1.55) : "#606060"
                contentItem: Image {
                    id: _imgMs
                    fillMode: Image.PreserveAspectFit
                    source: ResourcesProvider.imgCcCrMagicStick

                    transform: Scale {
                        id: _scaleImgMs
                        origin.x: _imgMs.width / 2
                        origin.y: _imgMs.height / 2
                    }
                }

                Connections {
                    function onClicked() {
                        _privPropsState.btnSt = _privPropsState.msSt;
                        _btnMs.applyAnim();
                    }
                }

                function applyAnim() {
                    _seqAnimMs.start();
                }

                SequentialAnimation {
                    id: _seqAnimMs
                    NumberAnimation {
                        target: _scaleImgMs
                        properties: "xScale"
                        to: 1.2
                        duration: 125
                    }
                    NumberAnimation {
                        target: _scaleImgMs
                        properties: "xScale"
                        to: 1
                        duration: 125
                    }
                }
            }
        }
    }
}
