import QtQuick
import QtQuick.Controls

import Qt5Compat.GraphicalEffects

import "../Widgets"

Rectangle {
    id: root
    color: "transparent"
    clip: true

    width: 480
    height: root.reqHeight

    readonly property real reqHeight: _recLbl.height + _btnNo.height + root.btnTopMgn
    property alias lblCnfrmText: _lblConfirm.text

    Rectangle {
        id: _recLbl
        height: _recInLbl.height + _recInLbl.mgns

        anchors.left: parent.left
        anchors.right: parent.right

        color: "#3B3B3B"
        radius: 7

        Rectangle {
            id: _recInLbl
            clip: true

            height: _lblConfirm.height

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            readonly property int mgns: 2
            anchors.topMargin: _recInLbl.mgns
            anchors.leftMargin: _recInLbl.mgns
            anchors.rightMargin: _recInLbl.mgns

            color: "#E1E2E1"
            radius: 7

            Label {
                id: _lblConfirm
                height: _lblConfirm.implicitHeight

                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right

                topPadding: 7
                bottomPadding: 7
                leftPadding: 5
                rightPadding: 5

                wrapMode: Label.Wrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                font.pointSize: 18
                color: "black"
                text: qsTr("Подтвердить?")
            }
        }

        InnerShadow {
            anchors.fill: _recInLbl
            source: _recInLbl
            radius: 1
            samples: 3
            horizontalOffset: 0
            verticalOffset: -2
            color: "#80000000"
        }
    }

    signal btnNoClicked()
    signal btnYesClicked()

    readonly property real btnTopMgn: 7
    readonly property real btnTxtFontSz: 20
    BtnWithBorder {
        id: _btnNo

        anchors.rightMargin: 3
        anchors.topMargin: root.btnTopMgn

        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        anchors.top: _recLbl.bottom

        bkgColor: "#616161"
        brdColor: "#3B3B3B"
        brdWidth: 2

        lblPadding: 9
        lblText: qsTr("Нет")
        txtFontSz: root.btnTxtFontSz

        onClicked: root.btnNoClicked()
    }

    BtnWithBorder {
        id: _btnYes

        anchors.leftMargin: 3
        anchors.topMargin: root.btnTopMgn

        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        anchors.top: _recLbl.bottom

        bkgColor: "#616161"
        brdColor: "#3B3B3B"
        brdWidth: 2

        lblPadding: 9
        lblText: qsTr("Да")
        txtFontSz: root.btnTxtFontSz

        onClicked: root.btnYesClicked()
    }
}
