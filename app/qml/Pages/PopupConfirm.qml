import QtQuick
import QtQuick.Controls

Popup {
    id: root
    modal: true

    margins: 0
    padding: 12

    // fwd!
    signal btnNoClicked()
    signal btnYesClicked()

    background: BgNewGamePopup {
    }

    property real reqHeight: _cntntPopupConfirm.reqHeight
    property alias lblCnfrmText: _cntntPopupConfirm.lblCnfrmText
    property alias cntntPopupConfirm: _cntntPopupConfirm
    contentItem: CntntPopupConfirm {
        id: _cntntPopupConfirm
        onBtnNoClicked: root.btnNoClicked()
        onBtnYesClicked: root.btnYesClicked()
    }
}
