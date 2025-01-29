import QtQuick
import QtQuick.Controls

Popup {
    id: root
    modal: true
    margins: 0

    property alias modeId: _cntntStatsPopup.modeId
    background: BgNewGamePopup {
    }

    contentItem: CntntStatsPopup {
        id: _cntntStatsPopup
    }
}
