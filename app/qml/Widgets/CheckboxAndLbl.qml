import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: root
    width: 480
    height: Math.max(_labelName.height, _itemCB.height)

    property alias lblNameText: _labelName.text
    property alias cbVal: _checkBox.checked

    Label {
        id: _labelName
        height: _labelName.implicitHeight
        anchors.verticalCenter: parent.verticalCenter

        anchors.left: parent.left
        anchors.right: _itemCB.left

        bottomPadding: 3
        topPadding: 3

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        wrapMode: Label.Wrap
        anchors.rightMargin: 0

        font.pixelSize: 18
    }

    Item {
        id: _itemCB
        width: _checkBox.width
        height: _checkBox.height

        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right

        CheckBox {
            id: _checkBox
            anchors.centerIn: parent
            width: 49
            height: 49

            indicator: Rectangle {
                id: _recEx
                implicitWidth: 35
                implicitHeight: 35
                x: _checkBox.leftPadding
                y: _checkBox.height / 2 - _recEx.height / 2

                radius: 3
                border.color: _checkBox.down ? Qt.lighter("#FF424242", 1.35) : "#FF424242"

                Rectangle {
                    id: _recIn
                    width: 21
                    height: 21
                    anchors.centerIn: parent

                    radius: 2
                    color: _checkBox.down ? Qt.lighter("#FF424242", 1.35) : "#FF424242"
                    visible: _checkBox.checked
                }
            }
        }
    }
}
