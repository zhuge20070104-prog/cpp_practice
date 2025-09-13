import QtQuick 2.12
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    Column {
        spacing: 2
        anchors.centerIn: parent 
        Repeater {
            model: ["Enterprise", "Columbia", "Challenger", "Discovery", "Endeavour", "Atlantis"]
            delegate: BlueBox {
                width: 120
                height: 32
                radius: 3
                text: index + ". " + modelData
            }
        }
    }
}


