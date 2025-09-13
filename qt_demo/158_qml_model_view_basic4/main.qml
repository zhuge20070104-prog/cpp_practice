import QtQuick 2.12
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    Background {
        width: 480
        height: 80
        ListView {
            anchors.fill: parent 
            anchors.margins: 20
            clip: true 
            model: 100
            orientation: ListView.Horizontal
            delegate: numberDelegate
            spacing: 5
        }

        Component {
            id: numberDelegate
            GreenBox {
                width: 40
                height: 40
                text: index
            }
        }
    }
}


