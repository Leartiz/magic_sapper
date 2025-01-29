import QtQuick
import QtQuick.Controls

import "qml/Pages"

ApplicationWindow {
    id: root
    width: 480
    height: 800
    visible: true

    title: qsTr("sapper")

    StackView {
        id: _stackView
        anchors.fill: parent
        focus: true

        Component.onCompleted: _stackView.push(_cmpntGameFieldPage)
    }

    Component {
        id: _cmpntGameFieldPage
        GameFieldPage {
            width: _stackView.width
            height: _stackView.height
        }
    }

    Component {
        id: _leaderboardPage
        LeaderboardPage {
            width: _stackView.width
            height: _stackView.height
        }
    }

    // SettgsPage in GameFieldPage!
}
