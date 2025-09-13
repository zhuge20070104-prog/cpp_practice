import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

Window {
    id: root
    visible: true
    width: 750
    height: 650
    Column {
        Row {
            id: tools 
            Button {
                text: "Reset"
                onClicked: {
                    display.fillMode = Image.Stretch
                    display.width = display.sourceSize.width
                    display.height = display.sourceSize.height 
                    display.anchors.centerIn = viewport
                    display.clip = false
                }
            }

            Button {
                text: "Stretch"
                onClicked: {
                    display.fillMode = Image.Stretch
                    display.width = 200
                    display.height = 100
                }
            }

            Button {
                text: "PreserveAspectFit"
                onClicked: {
                    display.fillMode = Image.PreserveAspectFit
                    display.width = 400
                    display.height = 400
                }
            }

            Button {
                text: "PreserveAspectCrop"
                onClicked: {
                    display.fillMode = Image.PreserveAspectCrop
                    display.width = 100
                    display.height = 400
                    display.clip = true
                }
            }

            Button {
                text: "Tile"
                onClicked: {
                    display.fillMode = Image.Tile
                    display.width = viewport.width
                    display.height = viewport.height
                }
            }


            Button {
                text: "TileHorizontally"
                onClicked: {
                    display.fillMode = Image.TileHorizontally
                    display.width = viewport.width
                    display.height = viewport.height
                }
            }

            Button {
                text: "TileVertically"
                onClicked: {
                    display.fillMode = Image.TileVertically
                    display.width = viewport.width
                    display.height = viewport.height
                }
            }
        }

        Rectangle {
            id: viewport
            width: root.width
            height: root.height

            AnimatedImage {
                id: display
                anchors.centerIn: parent 
                source: "images/qt_logo.jpg" 
            }
        }
    }
   
}
