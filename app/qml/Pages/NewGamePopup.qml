import QtQuick
import QtQuick.Controls

Popup {
    id: root
    modal: true
    margins: 0
    padding: 12

    // fwd!
    signal clickedMenuBtn()
    signal curModeChanged()

    onOpened: _cntntNewGamePopup.listViewToCurIndx()

    background: BgNewGamePopup {
    }

    contentItem: CntntNewGamePopup {
        id: _cntntNewGamePopup
        onClickedMenuBtn: root.clickedMenuBtn()
        onCurModeChanged: root.curModeChanged()
    }
}
