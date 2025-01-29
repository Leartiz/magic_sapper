import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 480
    height: _lbl.implicitHeight

    property alias imgSrc: _img.source
    property alias lblText: _lbl.text

    Item {
        id: _itemImg
        width: _itemImg.height
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        Image {
            id: _img
            anchors.fill: parent
            anchors.margins: 3
            fillMode: Image.PreserveAspectFit
        }
    }

    Label {
        id: _lbl
        anchors.left: _itemImg.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        verticalAlignment: Text.AlignVCenter
        wrapMode: Label.Wrap
        elide: Label.ElideRight
        leftPadding: 21
        padding: 9
        font.pointSize: 20
    }
}
