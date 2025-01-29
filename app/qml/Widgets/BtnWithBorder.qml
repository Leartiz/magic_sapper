import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    id: root
    clip: true

    height: _lbl.implicitHeight
    width: 250

    property string brdColor: "#E1E2E1"
    property real brdWidth: 3

    property string bkgColor: "#616161"
    property string txtColor: "white"
    property real txtFontSz: 22

    background: Rectangle {
        color: root.pressed ? Qt.lighter(root.bkgColor, 1.15) : root.bkgColor
        radius: 7

        border.width: root.brdWidth
        border.color: root.brdColor
    }

    property alias lblText: _lbl.text
    property alias lblPadding: _lbl.padding
    Label {
        id: _lbl
        anchors.fill: parent
        padding: 5

        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter

        elide: Label.ElideRight

        color: root.txtColor
        font.pointSize: root.txtFontSz
    }
}
