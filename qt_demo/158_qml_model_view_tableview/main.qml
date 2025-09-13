import QtQuick 2.12
import QtQuick.Window 2.0

Window {
    visible: true
    width: 320
    height: 320

    Background {
        anchors.fill: parent 
        TableView {
            id: view 
            anchors.fill: parent 
            anchors.margins: 20

            rowSpacing: 5
            columnSpacing: 5

            clip: true 
            model: tableModel 
            delegate: cellDelegate 
        }
    }


    Component {
        id: cellDelegate 
        GreenBox {
            implicitWidth: 40
            implicitHeight: 40
            Text {
                anchors.centerIn: parent 
                text: display 
            }
        }
    }
}


