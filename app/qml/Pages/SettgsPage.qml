import QtQuick
import QtQuick.Controls

import "../Bars"
import "../Widgets"
import "../Resources"

import SettgsModel 1.0

Page {
    id: root
    width: 480
    height: 800

    header: SettgsTopBar {
        id: _topBar
        onBtnBackClicked: root.backToGameFieldPage()
    }

    background: Rectangle {
        color: "#E1E2E1"
    }

    signal settgsSaved()

    Flickable {
        id: _flick
        z: 5
        anchors.fill: parent

        anchors.topMargin: 5
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        contentWidth: _flick.width
        contentHeight: _col.implicitHeight

        onMovingChanged: {
            // or short!
            if (_flick.moving) {
                _scrollInd.opacity = 1;
                return;
            }
            _scrollInd.opacity = 0;
        }

        ScrollIndicator.vertical: ScrollIndicator {
            id: _scrollInd
            anchors.right: parent.right
            rightPadding: 0
            leftPadding: 0
            opacity: 0

            contentItem: Rectangle {
                id: _recSI
                implicitWidth: 3
                radius: 3
                color: "#3B3B3B"
            }

            Behavior on opacity {
                NumberAnimation { duration: 100 }
            }
        }

        Column {
            id: _col
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            anchors.leftMargin: 23
            anchors.rightMargin: _recSI.width + _flick.anchors.rightMargin

            // header!
            Item {
                height: 10
                anchors.left: parent.left
                anchors.right: parent.right
            }

            ImgWithLbl {
                id: _iwlGamer
                lblText: qsTr("Игрок")
                imgSrc: ResourcesProvider.imgSettgsBasicUser
            }

            MenuSeparator {
                anchors.left: parent.left
                anchors.right: parent.right
            }

            Item {
                height: 10
                anchors.left: parent.left
                anchors.right: parent.right
            }

            EditableField {
                id: _nameEditField
                anchors.left: parent.left
                anchors.right: parent.right
                fieldName: qsTr("Имя")
                fieldValue: _settgsModel.username
                onFieldValueChanged: _privProps.isSomethingChanged = true
            }

            Item {
                height: 25
                anchors.left: parent.left
                anchors.right: parent.right
            }

            ImgWithLbl {
                id: _iwlControl
                lblText: qsTr("Управление")
                imgSrc: ResourcesProvider.imgSettgsBasicControl
            }

            MenuSeparator {
                anchors.left: parent.left
                anchors.right: parent.right
            }

            Item {
                height: 10
                anchors.left: parent.left
                anchors.right: parent.right
            }

            CheckboxAndLbl {
                id: _calQuestionMark
                anchors.left: parent.left
                anchors.right: parent.right
                lblNameText: qsTr("Вопросительный знак")
                cbVal: _settgsModel.isUseQuestionMark
                onCbValChanged: _privProps.isSomethingChanged = true
            }

            Item {
                height: 10
                anchors.left: parent.left
                anchors.right: parent.right
            }

            CheckboxAndLbl {
                id: _calSizeSlider
                anchors.left: parent.left
                anchors.right: parent.right
                lblNameText: qsTr("Ползунок размера")
                cbVal: _settgsModel.isUseSizeSlider
                onCbValChanged: _privProps.isSomethingChanged = true
            }

            Item {
                height: 25
                anchors.left: parent.left
                anchors.right: parent.right
            }

            ImgWithLbl {
                id: _iwlStats
                lblText: qsTr("Статистика")
                imgSrc: ResourcesProvider.imgStatsBasicStats
            }

            MenuSeparator {
                anchors.left: parent.left
                anchors.right: parent.right
            }

            Item {
                height: 10
                anchors.left: parent.left
                anchors.right: parent.right
            }

            Button {
                id: _btnClear
                anchors.left: parent.left
                anchors.right: parent.right
                text: qsTr("Очистить")

                onClicked: _rstStatsPopup.open()

                background: Rectangle {
                    implicitHeight: 50
                    opacity: _btnClear.enabled ? 1 : 0.3

                    color: _btnClear.pressed ? Qt.lighter("#c62828", 1.15) : "#c62828"
                    radius: 2
                }
                contentItem: Text {
                    opacity: _btnClear.enabled ? 1.0 : 0.3

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight

                    color: "white"
                    font.pixelSize: 18
                    text: _btnClear.text
                }
            }

            // footer!
            Item {
                height: 10
                anchors.left: parent.left
                anchors.right: parent.right
            }
        }
    }

    PopupConfirm {
        id: _rstStatsPopup

        y: _rstStatsPopup.verMgns - 50 // bar!
        x: _rstStatsPopup.horMgns

        readonly property real verMgns: (root.height - _rstStatsPopup.height) / 2
        readonly property real horMgns: 50

        width: root.width - _rstStatsPopup.horMgns * 2
        height: _rstStatsPopup.reqHeight + _rstStatsPopup.padding * 2

        lblCnfrmText: qsTr("Очистить статистику?")

        onBtnNoClicked: _rstStatsPopup.close()
        onBtnYesClicked: _settgsModel.resetStatsAndRecs()
    }

    SettgsModel {
        id: _settgsModel
        onSettgsSaved: root.settgsSaved()
        onStatsAndRecsReseted: _rstStatsPopup.close()
    }

    QtObject {
        id: _privProps
        property bool isSomethingChanged: false
    }
    // init!
    Component.onCompleted: _privProps.isSomethingChanged = false

    function backToGameFieldPage() {
        _nameEditField.focus = false; // sometimes empty?
        if (_privProps.isSomethingChanged) {
            const usrnm = _nameEditField.fieldValue.trim();
            const isUseQM = _calQuestionMark.cbVal;
            const isUseSS = _calSizeSlider.cbVal;

            _settgsModel.setSettgs(usrnm, isUseQM, isUseSS);
        }
        _stackView.pop();
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Escape || event.key === Qt.Key_Back) {
            root.backToGameFieldPage();
            event.accepted = true;
        }
    }
}
