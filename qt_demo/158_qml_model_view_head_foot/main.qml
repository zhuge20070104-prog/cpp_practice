import QtQuick 2.12
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true

    Background {
        width: 240
        height: 280

        ListView {
            id: view 
            anchors.fill: parent 
            anchors.margins: 20
            clip: true 
            model: 4

            delegate: numberDelegate
            spacing: 2

            header: headerComponent
            footer: footerComponent
        }

        Component {
            id: headerComponent
            YellowBox {
                width: ListView.view.width
                height: 20
                text: "Header"
            }
        }

        Component {
            id: footerComponent
            YellowBox {
                width: ListView.view.width
                height: 20
                text: "Footer"
            }
        }

        Component {
            id: numberDelegate
            GreenBox {
                width: ListView.view.width
                height: 40
                text: "Item " + index
            }
        }
    }
}


