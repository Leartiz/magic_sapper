import QtQuick
import QtQuick.Controls

import Qt5Compat.GraphicalEffects

import "../Resources"
import "../Widgets"

// use only with lb page!
ToolBar {
    id: root
    width: 480
    height: 100

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
        height: root.height / 2
        anchors.top: parent.top
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
        id: _imgLB
        width: _imgLB.height
        height: root.height / 2 - 6 // insets!
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        source: ResourcesProvider.imgIosWLeaderboard
        fillMode: Image.PreserveAspectFit
    }

    signal btnStatsClicked()
    BtnTopBar {
        id: _btnStats
        height: root.height / 2
        anchors.top: parent.top
        anchors.right: parent.right

        contentItem: Image {
            id: _imgStats

            fillMode: Image.PreserveAspectFit
            source: ResourcesProvider.imgIosWStats
        }

        Connections {
            target: _btnStats
            function onClicked() {
                root.btnStatsClicked();
            }
        }
    }

    property alias listViewMods: _listViewMods
    ListView {
        id: _listViewMods
        height: root.height / 2
        orientation: ListView.Horizontal

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        model: _smplModesModel
        delegate: SmplModeTab {
            id: _smplModeTb
            width: {
                const reqWidth = root.width / _listViewMods.count;
                const minWidth = _smplModeTb.lblModeNme.implicitWidth;
                if (reqWidth > minWidth)
                    return reqWidth;
                return minWidth;
            }

            lblModeNme.text: ModeName

            lblModeNme.color: {
                if (_smplModesModel.curIndx === index)
                    return "white";
                return Qt.darker("white", 1.25);
            }
            recSeld.color: {
                if (_smplModesModel.curIndx === index)
                    return "white";
                return "transparent";
            }

            Connections {
                target:_smplModeTb
                function onClicked() {
                    _smplModesModel.curIndx = index;
                    _listViewMods.positionViewAtIndex(index, ListView.Center);
                }
            }
        }
    }
}
