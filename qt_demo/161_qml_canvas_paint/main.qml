import QtQuick 2.12
import QtQuick.Controls 1.4


ApplicationWindow {
    visible: true
    
    Rectangle {
        width: 400
        height: 300
        color: "#333333"

        Row {
            id: colorTools
            
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top 
                topMargin: 8
            }

            property color paintColor: "#33B5E5"

            spacing: 4
            Repeater {
                model: ["#33B5E5", "#99CC00", "#FFBB33", "#FF4444"]
                ColorSquare {
                    id: red
                    color: modelData 
                    active: parent.paintColor === color
                    onClicked: {
                        parent.paintColor = color 
                        // active = true
                    }
                }
            }
            
        }

        Rectangle {
            anchors.fill: canvas 
            border.color: "#666666"
            border.width: 4
        }

        Canvas {
            id: canvas
            anchors {
                left: parent.left 
                right: parent.right 
                top: colorTools.bottom 
                bottom: parent.bottom 
                margins: 8
            }

            property real lastX 
            property real lastY 
            property color color: colorTools.paintColor 

            onPaint: {
                var ctx = getContext("2d")
                ctx.lineWidth = 1.5
                ctx.strokeStyle = canvas.color 
                ctx.beginPath()
                ctx.moveTo(lastX, lastY)
                lastX = area.mouseX 
                lastY = area.mouseY 
                ctx.lineTo(lastX, lastY)
                ctx.stroke()
            }

            MouseArea {
                id: area 
                anchors.fill: parent
                onPressed: {
                    canvas.lastX = mouseX 
                    canvas.lastY = mouseY 
                }

                onPositionChanged: {
                    canvas.requestPaint()
                }
            }
        }
    }   
}


