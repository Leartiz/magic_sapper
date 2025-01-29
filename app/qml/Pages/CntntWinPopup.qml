import QtQuick
import QtQuick.Controls

import "../Resources"
import "../Widgets"
import "../Pages/RandomInt.js" as RandomInt

Rectangle {
    id: root
    width: 480
    height: 800
    color: "transparent"

    property alias btnOk: _btnOk
    property alias timerAnimTo: _timerAnimTo
    function resetAnim() {
        root.state = "_st0";
        _behImgGl.enabled = true;
        _behImgSm.enabled = true;

        // recovery!
        _recLblWin.visible = false;
        _btnOk.visible = false;
        _imgGlasses.visible = true;
        _imgSmile.source = ResourcesProvider.imgSmilesSmileSt0;
    }

    Timer {
        id: _timerAnimTo
        interval: 50

        onTriggered: root.state = "_stWin"
    }

    Image {
        id: _imgGlasses
        y: -_imgGlasses.height
        z: 10
        width: _recShine.width
        height: _recShine.height

        anchors.horizontalCenter: parent.horizontalCenter
        source: ResourcesProvider.imgSmilesSmileGlasses
        fillMode: Image.PreserveAspectFit

        onYChanged: {
            if (!_behImgGl.enabled) return;
            const newY = root.height / 2 - _imgGlasses.height / 2;
            if (_imgGlasses.y === newY) {
                _behImgGl.enabled = false;
            }
            root.startNumAnimShineIfCan(); // one time!
        }

        Behavior on y {
            id: _behImgGl
            enabled: true
            NumberAnimation { duration: 250 }
        }
    }

    Image {
        id: _imgSmile
        y: root.height + 100 // bar height!
        width: _recShine.width
        height: _recShine.height

        anchors.horizontalCenter: parent.horizontalCenter
        source: ResourcesProvider.imgSmilesSmileSt0
        fillMode: Image.PreserveAspectFit

        onYChanged: {
            if (!_behImgSm.enabled) return;
            const newY = root.height / 2 - _imgSmile.height / 2;
            if (_imgSmile.y === newY) {
                _behImgSm.enabled = false;
            }
            root.startNumAnimShineIfCan();
        }

        Behavior on y {
            id: _behImgSm
            enabled: true
            NumberAnimation { duration: 250 }
        }
    }

    // with basic size!
    Rectangle {
        id: _recShine
        visible: false
        width: {
            const maxSideSz = 256;
            const minSideSz = 128;
            const off = 100 + 15; // bar height and margins!
            var curSideSz = Math.min(root.height, root.width) - off;
            if (maxSideSz < curSideSz)
                return maxSideSz;
            if (minSideSz > curSideSz)
                return minSideSz;
            return curSideSz;
        }
        height: _recShine.width
        radius: 128
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        gradient: Gradient {
            orientation: Gradient.Horizontal

            GradientStop { position: 0.0; color: "transparent" }
            GradientStop { id: _gStopLineShine; position: 0.0; color: "white" }
            GradientStop { position: 1.0; color: "transparent" }
        }
    }

    function startNumAnimShineIfCan() {
        if (_behImgGl.enabled === false && _behImgSm.enabled === false)
            _numAnimShine.start();
    }

    NumberAnimation {
        id: _numAnimShine
        target: _gStopLineShine
        properties: "position"
        from: 0
        to: 1
        duration: 100

        onStarted: {
            _recShine.visible = true;
            _recLblWin.visible = true;
            _btnOk.visible = true;
            _imgSmile.source = ResourcesProvider.imgSmilesSmileWin0;
        }

        onFinished: {
            // part reset!
            _recShine.visible = false;
            _gStopLineShine.position = 0;
            _imgGlasses.visible = false;
        }
    }

    function generateTextLblWin() {
        const rVal = RandomInt.getRandomInt(4);
        var txt = qsTr("Победа!");
        switch (rVal) {
        case 0:
            txt = qsTr("Победа!");
            break;
        case 1:
            txt = qsTr("Ура, ура, ура!");
            break;
        case 2:
            txt = qsTr("Sapper-hacker!");
            break;
        case 3:
            txt = qsTr("Неплохо.");
            break;
        }
        _lblWin.text = txt;
    }



    Rectangle {
        id: _recLblWin
        visible: false

        height: _lblWin.implicitHeight
        width: {
            const lblWinWidth = _lblWin.implicitWidth;

            if (root.width > lblWinWidth)
                return lblWinWidth;
            return root.width;
        }

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: _imgGlasses.top
        anchors.bottomMargin: 25

        gradient: Gradient {
            orientation: Gradient.Horizontal

            GradientStop { position: 0.0; color: "transparent" }
            GradientStop { position: 0.5; color: "#E11B1B1B" }
            GradientStop { position: 1.0; color: "transparent" }
        }

        Label {
            id: _lblWin

            anchors.left: parent.left
            anchors.right: parent.right

            topPadding: 5
            bottomPadding: 7

            leftPadding: 9
            rightPadding: 9

            elide: Label.ElideRight
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            color: "white"
            font.pointSize: 28
            text: qsTr("Победа!")
        }
    }

    BtnWithBorder {
        id: _btnOk
        visible: false
        width: _recShine.width - 15 // mgns!

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _imgSmile.bottom
        anchors.topMargin: 25

        lblText: qsTr("Ок")
    }

    // only for y!
    states: [
        State {
            name: "_st0"

            PropertyChanges {
                target: _imgGlasses
                y: -_imgGlasses.height
            }
            PropertyChanges {
                target: _imgSmile
                y: root.height + 100
            }
        },
        State {
            name: "_stWin"

            PropertyChanges {
                target: _imgGlasses
                y: root.height / 2 - _imgGlasses.height / 2
            }
            PropertyChanges {
                target: _imgSmile
                y: root.height / 2 - _imgSmile.height / 2
            }
        }
    ]
}
