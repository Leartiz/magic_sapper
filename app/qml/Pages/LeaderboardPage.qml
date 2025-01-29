import QtQuick
import QtQuick.Controls

import "../Bars"
import "../Widgets"
import "../Resources"

import SmplModesModel 1.0
import RecordsModel 1.0

Page {
    id: root

    header: LBoardTopBar {
        id: _topBar
        onBtnBackClicked: root.backToGameFieldPage();
        onBtnStatsClicked: _statsPopup.open()
    }

    footer: ModeBotBar {
        id: _botBar

        pIndCount: _swipeView.count
        pIndCurrentIndex: _swipeView.currentIndex
    }

    background: Rectangle {
        color: "#E1E2E1"
    }

    SwipeView {
        id: _swipeView
        anchors.fill: parent

        Repeater {
            model: _smplModesModel
            Loader {
                active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                sourceComponent: Item {
                    id: _itemSC
                    property int cpyIndexRptr: index

                    ListView {
                        id: _listViewRecs
                        anchors.fill: parent
                        anchors.leftMargin: 7
                        anchors.rightMargin: 7
                        anchors.topMargin: 7
                        anchors.bottomMargin: 7
                        spacing: 7

                        onMovingChanged: {
                            // or short!
                            if (_listViewRecs.moving) {
                                _scrollInd.opacity = 1;
                                return;
                            }
                            _scrollInd.opacity = 0;
                        }

                        ScrollIndicator.vertical: ScrollIndicator {
                            id: _scrollInd
                            anchors.right: parent.right
                            rightPadding: 0
                            leftPadding: 0
                            opacity: 0

                            contentItem: Rectangle {
                                id: _recSI
                                implicitWidth: 3
                                radius: 3
                                color: "#3B3B3B"
                            }

                            Behavior on opacity {
                                NumberAnimation { duration: 100 }
                            }
                        }

                        model: _recModel
                        delegate: RecordItem {
                            id: _recItem
                            width: _listViewRecs.width - _recSI.width - _listViewRecs.anchors.rightMargin

                            lblN.visible: !(index >= 0 && index <= 2)
                            lblN.text: index + 1

                            imgN.visible: !_recItem.lblN.visible
                            imgN.source: {
                                switch (index) {
                                case 0:
                                    return ResourcesProvider.imgStepsFrst;
                                case 1:
                                    return ResourcesProvider.imgStepsScnd;
                                case 2:
                                    return ResourcesProvider.imgStepsThrd;
                                }
                                return "";
                            }

                            lblUsername: Username
                            lblTimePassed: TimePassed
                        }
                    }

                    RecordsModel {
                        id: _recModel
                        modeId: _smplModesModel.getModeIdByIndx(_itemSC.cpyIndexRptr) // for generate!
                    }
                }
            }
        }

        Connections {
            target: _swipeView
            function onCurrentIndexChanged() {
                _smplModesModel.curIndx = _swipeView.currentIndex;
                _topBar.listViewMods.positionViewAtIndex(_smplModesModel.curIndx, ListView.Center);
            }
        }
    }

    StatsPopup {
        id: _statsPopup
        modeId: _smplModesModel.getModeIdByIndx(_smplModesModel.curIndx)

        y: _statsPopup.verMgns - 100 // bar!
        x: _statsPopup.horMgns

        readonly property real verMgns: 62.5
        readonly property real horMgns: 25

        width: root.width - _statsPopup.horMgns * 2
        height: root.height - _statsPopup.verMgns * 2
    }

    SmplModesModel {
        id: _smplModesModel
        onCurIndxChanged: _swipeView.currentIndex = _smplModesModel.curIndx // reverse!
    }

    function backToGameFieldPage() {
        _swipeView.visible = false;
        _topBar.listViewMods.visible = false;
        _stackView.pop();
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Escape || event.key === Qt.Key_Back) {
            root.backToGameFieldPage();
            event.accepted = true;
        }
    }
}
