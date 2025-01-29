import QtQuick
import QtQuick.Controls

Popup {
    id: root
    modal: true
    margins: 0

    onOpened: {
        _cntnt.generateTextLblWin();
        _cntnt.timerAnimTo.start();
    }

    onClosed: _cntnt.resetAnim()

    background: Rectangle {
        color: "transparent"
    }

    contentItem: CntntWinPopup {
        id: _cntnt
        btnOk.onClicked: root.close()
    }
}
