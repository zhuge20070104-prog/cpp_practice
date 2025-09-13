import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "green"

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("A bit info...")
            Qt.quit()
        }
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
}
