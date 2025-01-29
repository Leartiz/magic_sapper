import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    width: 400
    height: _lblUN.implicitHeight + _lblTP.implicitHeight
    color: Qt.darker("#FF606060", 1.30)

    property alias imgN: _imgN
    property alias lblN: _lblN

    property alias lblUsername: _lblUN.text
    property alias lblTimePassed: _lblTP.text

    Label {
        id: _lblUN
        anchors.left: _itemNumber.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.verticalCenter
        anchors.rightMargin: 25
        anchors.leftMargin: 25
        padding: 5
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Label.ElideRight
        font.pointSize: 18
        color: "white"
        text: qsTr("UN")
    }

    Label {
        id: _lblTP
        anchors.left: _itemNumber.right
        anchors.right: parent.right
        anchors.top: parent.verticalCenter
        anchors.bottom: parent.bottom
        anchors.rightMargin: 50
        anchors.leftMargin: 25
        padding: 5
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        elide: Label.ElideRight
        font.pointSize: 16
        color: "white"
        text: qsTr("TP")
    }

    Item {
        id: _itemNumber
        width: 75
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        Rectangle {
            id: _recBack
            color: "#801b1b1b"
            radius: 0
            anchors.fill: parent

            Image {
                id: _imgN
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                z: 5
                anchors.margins: 11
                anchors.rightMargin: 9
                anchors.leftMargin: 9
                anchors.topMargin: 9
                anchors.bottomMargin: 9
                fillMode: Image.PreserveAspectFit
            }

            Label {
                id: _lblN
                z: 5
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 18
                color: "white"
                text: qsTr("N")
            }
        }
    }
}
