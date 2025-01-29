import QtQuick 2.12
import QtQuick.Controls 2.12

import "../Resources"

Item {
    id: root
    width: 320
    height: 240

    property alias sliderBombs: _sliderBombs
    property alias sliderCols: _sliderCols
    property alias sliderRows: _sliderRows

    PrmModeSlider {
        id: _sliderRows
        width: root.width / 3
        anchors.left: parent.left
        anchors.top: _lblRows.bottom
        anchors.bottom: _imgRows.top
        orientation: Qt.Vertical
        stepSize: 1
    }

    Label {
        id: _lblRows
        height: _lblRows.implicitHeight
        width: root.width / 3
        anchors.left: parent.left
        anchors.top: parent.top
        font.pointSize: 18
        elide: Label.ElideRight
        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter
        text: _sliderRows.value
    }

    PrmModeSlider {
        id: _sliderCols
        width: root.width / 3
        anchors.top: _lblCols.bottom
        anchors.left: _sliderRows.right
        anchors.bottom: _imgCols.top
        anchors.bottomMargin: 0
        orientation: Qt.Vertical
        stepSize: 1
    }

    Label {
        id: _lblCols
        width: root.width / 3
        anchors.top: parent.top
        font.pointSize: 18
        elide: Label.ElideRight
        anchors.left: _lblRows.right
        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter
        text: _sliderCols.value
    }

    PrmModeSlider {
        id: _sliderBombs
        width: root.width / 3
        anchors.top: _lblBombs.bottom
        anchors.left: _sliderCols.right
        anchors.bottom: _imgBombs.top
        anchors.bottomMargin: 0
        orientation: Qt.Vertical
        stepSize: 1
    }

    Label {
        id: _lblBombs
        width: root.width / 3
        anchors.left: _lblCols.right
        anchors.top: parent.top
        font.pointSize: 18
        elide: Label.ElideRight
        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter
        text: _sliderBombs.value
    }

    Image {
        id: _imgRows
        width: root.width / 3
        height: 40
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        fillMode: Image.PreserveAspectFit
        source: ResourcesProvider.imgTblRows
    }

    Image {
        id: _imgCols
        width: root.width / 3
        height: 40
        anchors.left: _imgRows.right
        anchors.bottom: parent.bottom
        source: ResourcesProvider.imgTblCols
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: _imgBombs
        width: root.width / 3
        height: 40
        anchors.left: _imgCols.right
        anchors.bottom: parent.bottom
        source: ResourcesProvider.imgBombsBomb3
        fillMode: Image.PreserveAspectFit
    }
}
