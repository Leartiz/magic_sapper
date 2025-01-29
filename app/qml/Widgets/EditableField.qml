import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: root

    width: 480
    height: _labelName.height + _textFieldValue.height
    color: "transparent"

    property alias fieldName: _labelName.text
    property alias fieldValue: _textFieldValue.text

    // objects
    property alias refLabelName: _labelName
    property alias refTextFieldValue: _textFieldValue

    Label {
        id: _labelName
        height: _labelName.implicitHeight

        anchors.left: parent.left
        anchors.right: parent.right

        bottomPadding: 3
        topPadding: 3

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        wrapMode: Label.Wrap

        font.pixelSize: 16
    }

    TextField {
        id: _textFieldValue
        height: _textFieldValue.implicitHeight

        anchors.top: _labelName.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        bottomPadding: 3
        topPadding: 3

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        wrapMode: TextField.Wrap

        maximumLength: 25
        font.pixelSize: 18

        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 40

            color: {
                if (_textFieldValue.length === 0 && !_textFieldValue.focus) {
                    return "#C61A1A";
                }
                return "white";
            }

            // basic!
            border.color: _textFieldValue.focus ? "#FF0066FF" : "#FFBDBDBD"
            border.width: _textFieldValue.focus ? 2 : 1
        }
    }
}
