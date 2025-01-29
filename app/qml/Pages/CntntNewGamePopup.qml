import QtQuick
import QtQuick.Controls

import Qt5Compat.GraphicalEffects

import "../Widgets"
import "../Resources"

import ModesModel 1.0
import CustomModeModel 1.0
import WrMode 1.0

Rectangle {
    id: root
    width: 480
    height: 800
    color: "transparent"

    signal clickedMenuBtn()
    signal curModeChanged()

    onWidthChanged: root.changeOrientationIfNeed()
    onHeightChanged: root.changeOrientationIfNeed()

    function listViewToCurIndx() {
        _listViewMBtns.positionViewAtIndex(_modesModel.curIndx, ListView.Center);
    }

    Rectangle {
        id: _recListView
        color: "#3B3B3B"
        radius: 7

        Rectangle {
            id: _recInListView
            clip: true
            anchors.fill: parent
            anchors.margins: 2
            color: "#E1E2E1"
            radius: 7

            ListView {
                id: _listViewMBtns
                anchors.fill: parent
                // for each!
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                anchors.topMargin: 5
                anchors.bottomMargin: 5
                spacing: 5

                ScrollIndicator.vertical: ScrollIndicator {
                    id: _scrollInd
                    anchors.right: parent.right
                    rightPadding: 0
                    leftPadding: 0

                    contentItem: Rectangle {
                        id: _recSI
                        implicitWidth: 3
                        radius: 3 // does not work?
                        color: "#3B3B3B"
                    }
                }

                model: _modesModel
                delegate: MenuBtn {
                    id: _menuBtn
                    width: _listViewMBtns.width - _recSI.width - _listViewMBtns.anchors.rightMargin

                    lblModeText: ModeName
                    lblSizesText: NumRows + "×" + NumCols + ", " + AmBombs + " бомб"

                    imageCurMode.source: _menuBtn.imageCurMode.visible ? ResourcesProvider.imgBombsBomb3 : ""
                    imageCurMode.visible: _modesModel.curMode === ModeEnum

                    Connections {
                        target: _menuBtn
                        function onClicked() {
                            if (!_menuBtn.imageCurMode.visible) {
                                _modesModel.setCurModeId(ModeId);
                                root.curModeChanged();
                            }
                            root.clickedMenuBtn();
                        }
                    }
                }
            }
        }

        InnerShadow {
            anchors.fill: _recInListView
            source: _recInListView
            radius: 1
            samples: 3
            horizontalOffset: 0
            verticalOffset: -2
            color: "#80000000"
        }
    }

    Rectangle {
        id: _recCustomModeSldrs
        color: "#3B3B3B"
        radius: 7

        Rectangle {
            id: _recInCustomModeSldrs
            clip: true
            anchors.fill: parent
            anchors.margins: 2
            color: "#E1E2E1"
            radius: 7

            CustomModeSliders {
                id: _customModeSliders
                anchors.fill: parent
                anchors.margins: 5

                sliderRows.from: 9
                sliderRows.to: 30
                sliderRows.value: _customModeModel.numRows

                sliderCols.from: 9
                sliderCols.to: 30
                sliderCols.value: _customModeModel.numCols

                sliderBombs.from: 1
                sliderBombs.to: Math.floor(sliderRows.value * sliderCols.value / 3)
                sliderBombs.value: _customModeModel.amBombs

                // focus!
                sliderRows.onPressedChanged: _customModeSliders.onSliderRowsPressedChanged()
                sliderCols.onPressedChanged: _customModeSliders.onSliderColsPressedChanged()
                sliderBombs.onPressedChanged: _customModeSliders.onSliderBombsPressedChanged()

                function onSliderRowsPressedChanged() {
                    _listViewMBtns.positionViewAtEnd();

                    if (sliderRows.pressed) return;
                    if (_customModeModel.numRows === sliderRows.value) return;

                    _customModeModel.numRows = sliderRows.value;
                    _customModeModel.amBombs = sliderBombs.value
                }
                function onSliderColsPressedChanged() {
                    _listViewMBtns.positionViewAtEnd();

                    if (sliderCols.pressed) return;
                    if (_customModeModel.numCols === sliderCols.value) return;

                    _customModeModel.numCols = sliderCols.value;
                    _customModeModel.amBombs = sliderBombs.value
                }
                function onSliderBombsPressedChanged() {
                    _listViewMBtns.positionViewAtEnd();

                    if (sliderBombs.pressed) return;
                    if (_customModeModel.amBombs === sliderBombs.value) return;

                    _customModeModel.amBombs = sliderBombs.value
                }
            }
        }

        InnerShadow {
            anchors.fill: _recInCustomModeSldrs
            source: _recInCustomModeSldrs
            radius: 1
            samples: 3
            horizontalOffset: 0
            verticalOffset: -2
            color: "#80000000"
        }
    }


    ModesModel {
        id: _modesModel
    }

    CustomModeModel {
        id: _customModeModel

        // some lines!
        onCustomDModeChanged: {
            _modesModel.updCustomDMode();
            if (_modesModel.curMode === WrMode.Custom)
                _gameFieldModel.isNeedUpd = true;
        }
    }

    function changeOrientationIfNeed() {
        const genMargin = 15;
        // general!
        _recListView.anchors.top = root.top;
        _recListView.anchors.left = root.left;

        _recListView.anchors.rightMargin = 0;
        _recListView.anchors.bottomMargin = 0;

        _recCustomModeSldrs.anchors.top = undefined;
        _recCustomModeSldrs.anchors.left = undefined;

        _recCustomModeSldrs.anchors.right = root.right;
        _recCustomModeSldrs.anchors.bottom = root.bottom;

        if (root.width >= root.height) {
            _recListView.anchors.bottom = root.bottom;
            _recListView.anchors.right = _recCustomModeSldrs.left;
            _recListView.anchors.rightMargin = genMargin;

            _recCustomModeSldrs.anchors.top = root.top;
            _recCustomModeSldrs.width = root.width / 2 - genMargin
            return;
        }
        _recListView.anchors.right = root.right;
        _recListView.anchors.bottom = _recCustomModeSldrs.top;
        _recListView.anchors.bottomMargin = genMargin;

        _recCustomModeSldrs.anchors.left = root.left;
        _recCustomModeSldrs.height = root.height / 2 - genMargin;
    }
}
