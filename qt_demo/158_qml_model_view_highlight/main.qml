import QtQuick 2.12
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true

    Background {
        width: 240
        height: 300
        ListView {
            id: view 
            anchors.fill: parent 
            anchors.margins: 20
            clip: true 
            model: 100

            delegate: numberDelegate
            spacing: 5

            highlight: highlightComponent
            focus: true  
        }

        Component {
            id: highlightComponent
            GreenBox {
                width: ListView.view.width
            }
        }

        Component {
            id: numberDelegate
            Item {
                width: ListView.view.width
                height: 40
                Text {
                    id: text
                    anchors.centerIn: parent 
                    font.pixelSize: 10
                    text: index 
                }

                MouseArea {
                    anchors.fill: parent  
                    onClicked: {
                        view.currentIndex = index
                    }
                }
            }
        }
    }
}


