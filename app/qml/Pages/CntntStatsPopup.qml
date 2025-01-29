import QtQuick
import QtQuick.Controls

import Qt5Compat.GraphicalEffects

import "../Resources"

import StatsModel 1.0

Rectangle {
    id: root
    color: "transparent"
    clip: true
    width: 480
    height: 800

    Image {
        id: _imgStats
        height: 60
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.topMargin: 10
        fillMode: Image.PreserveAspectFit
        source: ResourcesProvider.imgStatsBasicStats
    }

    Rectangle {
        id: _recCol
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: _imgStats.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 10

        color: "#3B3B3B"
        radius: 7

        Rectangle {
            id: _recInCol
            clip: true
            anchors.fill: parent
            anchors.margins: 2
            color: "#E1E2E1"
            radius: 7

            Flickable {
                id: _flick
                anchors.fill: parent

                anchors.topMargin: 5
                anchors.bottomMargin: 5
                anchors.leftMargin: 5
                anchors.rightMargin: 5

                contentWidth: _flick.width
                contentHeight: _col.implicitHeight

                ScrollIndicator.vertical: ScrollIndicator {
                    id: _scrollInd
                    anchors.right: parent.right
                    rightPadding: 0
                    leftPadding: 0

                    contentItem: Rectangle {
                        id: _recSI
                        implicitWidth: 3
                        radius: 3
                        color: "#3B3B3B"
                    }
                }

                Column {
                    id: _col
                    anchors.left: parent.left
                    anchors.right: parent.right

                    anchors.rightMargin: _recSI.width + _flick.anchors.rightMargin
                    spacing: 5

                    readonly property real pdng: 10
                    readonly property real pntSz: 16

                    Label {
                        id: _lblAmGms
                        anchors.left: parent.left
                        anchors.right: parent.right
                        topPadding: _col.pdng
                        bottomPadding: _col.pdng
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Label.Wrap
                        elide: Label.ElideRight
                        font.pointSize: _col.pntSz
                        text: qsTr("Всего игр: ") + _statsModel.amGams
                    }

                    Label {
                        id: _lblAmWins
                        anchors.left: parent.left
                        anchors.right: parent.right
                        topPadding: _col.pdng
                        bottomPadding: _col.pdng
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Label.Wrap
                        elide: Label.ElideRight
                        font.pointSize: _col.pntSz
                        text: qsTr("Побед: ") + _statsModel.amWins
                    }

                    Label {
                        id: _lblPercentWin
                        anchors.left: parent.left
                        anchors.right: parent.right
                        topPadding: _col.pdng
                        bottomPadding: _col.pdng
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Label.Wrap
                        elide: Label.ElideRight
                        font.pointSize: _col.pntSz
                        text: qsTr("Процент выигрышей: ") + _statsModel.percentWin.toFixed(2) + "%"
                    }

                    Label {
                        id: _lblAmWinsInRow
                        anchors.left: parent.left
                        anchors.right: parent.right
                        topPadding: _col.pdng
                        bottomPadding: _col.pdng
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Label.Wrap
                        elide: Label.ElideRight
                        font.pointSize: _col.pntSz
                        text: qsTr("Побед подряд: ") + _statsModel.amWinsInRow
                    }

                    Label {
                        id: _lblAmLossInRow
                        anchors.left: parent.left
                        anchors.right: parent.right
                        topPadding: _col.pdng
                        bottomPadding: _col.pdng
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Label.Wrap
                        elide: Label.ElideRight
                        font.pointSize: _col.pntSz
                        text: qsTr("Проигрышей подряд: ") + _statsModel.amLossInRow
                    }
                }
            }
        }

        InnerShadow {
            anchors.fill: _recInCol
            source: _recInCol
            radius: 1
            samples: 3
            horizontalOffset: 0
            verticalOffset: -2
            color: "#80000000"
        }
    }

    property alias modeId: _statsModel.modeId
    StatsModel {
        id: _statsModel
    }
}
