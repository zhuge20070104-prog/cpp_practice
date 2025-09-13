import QtQuick 2.12
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    Column {
        spacing: 2
        anchors.centerIn: parent 
        Repeater {
            model: 10
            delegate: BlueBox {
                width: 120
                height: 32
                text: index
            }
        }
    }
}


