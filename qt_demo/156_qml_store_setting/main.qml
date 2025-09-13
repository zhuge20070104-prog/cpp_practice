import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import Qt.labs.settings 1.0


Window {
    id: root
    visible: true
    width: 640
    height: 480
    color: "#fff"
    title: qsTr("Settings Storage Demo")
    Settings {
        property alias color: root.color
    }

    MouseArea {
        anchors.fill: parent 
        onClicked: root.color = Qt.hsla(Math.random(), 0.5, 0.5, 1.0) 
    }
}
