import QtQuick
import QtQuick.Controls

import "../Widgets"
import "../Resources"
import "../Bars"

import "RandomInt.js" as RandomInt

import GameFieldModel 1.0
import WrCellType 1.0

Page {
    id: root
    width: 480
    height: 800
    readonly property real actualRootHeight: root.height - _topBar.height - _botBar.height

    onWidthChanged: _flick.calcAndSetContentXY()
    onActualRootHeightChanged: _flick.calcAndSetContentXY()

    header: GameFieldTopBar {
        id: _topBar

        labelBomb: _gameFieldModel.amBombs
        labelTime: _gameFieldModel.spendTime

        Connections {
            target: _topBar
            function onBtnLBClicked() {
                _stackView.push(_leaderboardPage);
            }
            function onBtnNewGameClicked() {
                _newGamePopup.open();
            }
            function onBtnSettingsClicked() {
                _stackView.push(_settgsPage);
            }
        }
    }

    Component {
        id: _settgsPage
        SettgsPage {
            width: _stackView.width
            height: _stackView.height

            onSettgsSaved: _gameFieldModel.updatePartSettgs()
        }
    }

    footer: ToolsBottomBar {
        id: _botBar
        numAvblPromt:_gameFieldModel.numAvblPromt

        btnQuestion.state: {
            if (_gameFieldModel.isUseQuestionMark)
                return _botBar.btnQuestion.stDefault;
            return _botBar.btnQuestion.stHidden;
        }

        Connections {
            target: _botBar
            function onToolSelected(tool) {
                _gameFieldModel.setNowTool(tool);
            }
            function onBtnPromptClicked() {
                _gameFieldModel.usePrompt();
            }
        }
    }

    background: Rectangle {
        color: "#E1E2E1"
    }

    Flickable {
        id: _flick
        clip: true

        width: Math.min(root.width, _flick.contentWidth)
        height: Math.min(root.actualRootHeight, _flick.contentHeight)

        anchors.centerIn: parent

        contentWidth: _grid.overCalculatedWidth
        contentHeight: _grid.overCalculatedHeight

        function calcAndSetContentXY() {
            _flick.contentX = _flick.calcContentX();
            _flick.contentY = _flick.calcContentY();
        }

        function calcContentX() {
            if (_flick.contentWidth < root.width) return 0;
            return (_flick.contentWidth - root.width) / 2;
        }
        function calcContentY() {
            if (_flick.contentHeight < root.actualRootHeight) return 0;
            return (_flick.contentHeight - root.actualRootHeight) / 2;
        }

        Component.onCompleted: _flick.calcAndSetContentXY()

        Grid {
            id: _grid
            padding: 50
            anchors.centerIn: parent
            z: 25

            // implicitHeight and implicitWidth bug?
            readonly property real overCalculatedWidth: _grid.scale * (_grid.columns * _grid.sideSzFieldCell + 2 * _grid.padding)
            readonly property real overCalculatedHeight: _grid.scale * (_grid.rows * _grid.sideSzFieldCell + 2 * _grid.padding)

            verticalItemAlignment: Grid.AlignVCenter
            horizontalItemAlignment: Grid.AlignHCenter

            // by signals upd!?
            rows: _gameFieldModel.rowAm
            columns: _gameFieldModel.colAm

            readonly property real sideSzFieldCell: 50
            Repeater {
                id: _repeaterCell
                model: _gameFieldModel
                delegate: FieldCell {
                    id: _fieldCell

                    // default sz!
                    width: _grid.sideSzFieldCell
                    height: _grid.sideSzFieldCell

                    isVisibleCntnt: {                        
                        if (CellData === WrCellType.Unknown ||
                                CellData === WrCellType.Question || CellData === WrCellType.Flag)
                            return true;
                        return false;
                    }
                    imgExtraStateSrc: {                        
                        if (CellData === WrCellType.Bomb_flag)
                            return ResourcesProvider.imgCcCrFlag;
                        if (CellData === WrCellType.Bomb_question)
                            return ResourcesProvider.imgCcCrQuestion;

                        return "";
                    }
                    imgMainStateSrc: {
                        if (CellData === WrCellType.Flag)
                            return ResourcesProvider.imgCcCrFlag;
                        if (CellData === WrCellType.Question)
                            return ResourcesProvider.imgCcCrQuestion;

                        if (CellData === WrCellType.Num_1)
                            return ResourcesProvider.imgNumsNum1;
                        if (CellData === WrCellType.Num_2)
                            return ResourcesProvider.imgNumsNum2;
                        if (CellData === WrCellType.Num_3)
                            return ResourcesProvider.imgNumsNum3;
                        if (CellData === WrCellType.Num_4)
                            return ResourcesProvider.imgNumsNum4;
                        if (CellData === WrCellType.Num_5)
                            return ResourcesProvider.imgNumsNum5;
                        if (CellData === WrCellType.Num_6)
                            return ResourcesProvider.imgNumsNum6;
                        if (CellData === WrCellType.Num_7)
                            return ResourcesProvider.imgNumsNum7;
                        if (CellData === WrCellType.Num_8)
                            return ResourcesProvider.imgNumsNum8;

                        if (CellData === WrCellType.Bomb)
                            return ResourcesProvider.imgBombsBomb3;
                        if (CellData === WrCellType.Bomb_flag)
                            return ResourcesProvider.imgBombsBomb3;
                        if (CellData === WrCellType.Bomb_question)
                            return ResourcesProvider.imgBombsBomb3;

                        return "";
                    }

                    MouseArea {
                        anchors.fill: parent
                        enabled: !_gameFieldModel.isEndGame
                        onClicked: {
                            _gameFieldModel.setCellData(index)
                        }
                        onPressAndHold: {
                            _botBar.setFlag();
                        }
                    }
                }
            }

            property real prevScale: 1.0
            onScaleChanged: {
                // calc offsets!
                if (implicitWidth * scale > _flick.width) {
                    var xOff = (_flick.width / 2 + _flick.contentX) * scale / prevScale;
                    _flick.contentX = xOff - _flick.width / 2
                }
                if (implicitHeight * scale > _flick.height) {
                    var yOff = (_flick.height / 2 + _flick.contentY) * scale / prevScale;
                    _flick.contentY = yOff - _flick.height / 2
                }
                prevScale = scale;
                _sizeSliderWithBtn.basicSlider.value = scale;
            }
        }

        PinchArea {
            id: _pinchArea
            z: 15

            anchors.fill: parent
            pinch.target: _grid
            pinch.minimumScale: 0.1
            pinch.maximumScale: 4.0
            pinch.dragAxis: Pinch.XAndYAxis

            MouseArea {
                anchors.fill: parent
            }
        }
    }

    SizeSliderWithBtn {
        id: _sizeSliderWithBtn
        visible: _gameFieldModel.isUseSizeSlider

        basicSlider.from: _pinchArea.pinch.minimumScale
        basicSlider.to: _pinchArea.pinch.maximumScale

        basicBgSlider.implicitHeight: {
            const rqHeight = 300;
            const rootHeight = root.actualRootHeight;

            const pdng = 50; // top, bot
            const genSpcng = sizeSlider.spacing * 2; // column

            if (rootHeight < rqHeight && rootHeight > basicSlider.width * 3 + pdng + genSpcng) {
                return rootHeight - basicSlider.width * 2 - pdng;
            }
            if (rootHeight > rqHeight) {
                return rqHeight - basicSlider.width * 2 - pdng;
            }
            return basicSlider.width;
        }
        basicSlider.visible: basicBgSlider.implicitHeight > basicSlider.width

        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        //anchors.rightMargin: 5

        Connections {
            target: _sizeSliderWithBtn
            function onZoomChanged(val) {
                _grid.scale = val;
            }
        }
    }

    NewGamePopup {
        id: _newGamePopup
        anchors.centerIn: parent

        readonly property real verMgns: 62.5
        readonly property real horMgns: 25

        width: root.width - _newGamePopup.horMgns * 2
        height: root.height - _newGamePopup.verMgns * 2

        Connections {
            target: _newGamePopup
            function onClickedMenuBtn() {
                _gameFieldModel.startNewGame();
                _newGamePopup.close();
                _botBar.setShvl();
            }
            function onCurModeChanged() {
                _gameFieldModel.updatePartFields();
            }
        }
    }

    WinPopup {
        id: _winPopup
        anchors.centerIn: parent

        width: root.width
        height: root.height
    }

    PopupConfirm {
        id: _exitPopup
        anchors.centerIn: parent

        readonly property real horMgns: 50
        width: root.width - _exitPopup.horMgns * 2
        height: _exitPopup.reqHeight + _exitPopup.padding * 2

        lblCnfrmText: qsTr("Закрыть приложение?")

        onBtnNoClicked: _exitPopup.close()
        onBtnYesClicked: Qt.quit()
    }

    PopupConfirm {
        id: _numAvblPromtEmptyPopup
        anchors.centerIn: parent

        readonly property real horMgns: 50
        width: root.width - _numAvblPromtEmptyPopup.horMgns * 2
        height: _numAvblPromtEmptyPopup.reqHeight + _numAvblPromtEmptyPopup.padding * 2

        lblCnfrmText: qsTr("Подсказки закончились! Использовать еще и не сохранять рекорд?")

        onBtnNoClicked: _numAvblPromtEmptyPopup.close()
        onBtnYesClicked: {
            _gameFieldModel.setFlagByIndxForUsePrompt();
            _numAvblPromtEmptyPopup.close();
        }
    }

    GameFieldModel {
        id: _gameFieldModel
    }

    Connections {
        target: _gameFieldModel
        function onLayoutChanged() {
            _flick.calcAndSetContentXY();
        }

        function onNewGameStarted() {
            _topBar.imgNewGame.source = ResourcesProvider.imgSmilesSmileSt0;
        }

        function onOpenedPartField() {
            _seqAnimImgNewGameScs.start();
        }
        function onNumAvblPromtEmptied() {
            _numAvblPromtEmptyPopup.open();
        }

        function onGameLosed() {
            _numAnimFrstImgNewGameLos.start();
        }
        function onGameWined() {
            _numAnimFrstImgNewGameWin.start();
            _winPopup.open();
        }

        // ***

        function onSideSizesWillChanged() {
            _grid.visible = false;
            console.log("_grid.visible: " + String(_grid.visible))
        }
        function onSideSizesChanged() {
            _grid.visible = true;
            console.log("_grid.visible: " + String(_grid.visible))
        }
    }

    SequentialAnimation {
        id: _seqAnimImgNewGameScs
        NumberAnimation {
            target: _topBar.imgNewGame
            properties: "scale"
            to: 1.1
            duration: 75
        }

        PauseAnimation {
            duration: 250
        }

        NumberAnimation {
            target: _topBar.imgNewGame
            properties: "scale"
            to: 1
            duration: 75
        }
        onStarted: root.setImgNewGameScs()
        onFinished: _topBar.imgNewGame.source = ResourcesProvider.imgSmilesSmileSt0
    }

    NumberAnimation {
        id: _numAnimFrstImgNewGameLos
        target: _topBar.imgNewGame
        properties: "scale"
        to: 0.9
        duration: 150
        onFinished: root.setImgNewGameLos()
    }
    NumberAnimation {
        id: _numAnimScndImgNewGameLos
        target: _topBar.imgNewGame
        properties: "scale"
        to: 1
        duration: 250
    }

    NumberAnimation {
        id: _numAnimFrstImgNewGameWin
        target: _topBar.imgNewGame
        properties: "scale"
        to: 0.9
        duration: 150
        onFinished: root.setImgNewGameWin()
    }
    NumberAnimation {
        id: _numAnimScndImgNewGameWin
        target: _topBar.imgNewGame
        properties: "scale"
        to: 1
        duration: 250
    }

    function setImgNewGameScs() {
        const rNum = RandomInt.getRandomInt(3);
        var imgSmilesSmileScs = ResourcesProvider.imgSmilesSmileScs0;
        switch (rNum) {
        case 0:
            imgSmilesSmileScs = ResourcesProvider.imgSmilesSmileScs0;
            break;
        case 1:
            imgSmilesSmileScs = ResourcesProvider.imgSmilesSmileScs1;
            break;
        case 2:
            imgSmilesSmileScs = ResourcesProvider.imgSmilesSmileScs2;
            break;
        }
        _topBar.imgNewGame.source = imgSmilesSmileScs;

        _numAnimScndImgNewGameWin.start();
    }

    function setImgNewGameWin() {
        _topBar.imgNewGame.source = ResourcesProvider.imgSmilesSmileWin0;
    }

    function setImgNewGameLos() {
        const rNum = RandomInt.getRandomInt(2);
        var imgLos = ResourcesProvider.imgSmilesSmileLos0;
        switch (rNum) {
        case 0:
            imgLos = ResourcesProvider.imgSmilesSmileLos0;
            break;
        case 1:
            imgLos = ResourcesProvider.imgSmilesSmileLos1;
            break;
        }
        _topBar.imgNewGame.source = imgLos;

        _numAnimScndImgNewGameLos.start(); // extra!
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Escape || event.key === Qt.Key_Back) {
            _exitPopup.open();
            event.accepted = true;
        }
    }
}
