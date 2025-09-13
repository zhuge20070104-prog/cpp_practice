import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.3

Window {
    id: root
    visible: true
    width: 500
    height: 500

    property bool running: false

    Rectangle {
        id: body
        width: root.width
        height: root.height 

        Image {
            id: background
            source: "qrc:///images/background.jpg"
            anchors.centerIn: body
            fillMode: Image.PreserveAspectFit
            width: 1350 
            RotationAnimation on rotation {
                from: 0
                to: -360
                duration: 3000
                running: root.running
                loops: Animation.Infinite
            }
        } 

        Image {
            id: smile 
            source: "qrc:///images/smile.jpg"
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: background 
            opacity: 0.5
        }

        MouseArea {
            anchors.fill:  background
            onClicked: {
                if(root.running == false) {
                    root.running = true 
                } else {
                    root.running = false
                    background.rotation = 0
                }
            }
        }
       
    }
}
