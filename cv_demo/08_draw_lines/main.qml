import QtQuick 2.12
import Qt.labs.platform 1.1
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.2



ApplicationWindow
{
    id: window
    visible: true
    title: qsTr("OpenCV图像处理助手")
    color:"#FFFFFF"
    x:0
    y:0

    property var start_x: 10
    property var start_y: 10
    property var shift: 5
    property var thickness: 10
    property var radius: 50

    width: 2000; height: 1000
    menuBar: MenuBar
    {
        Menu
        {
            title: qsTr("绘制")
            MenuItem
            {
                text: qsTr("画图")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
                    window.updateMat()
                 }
            }

            MenuSeparator {}
            MenuItem
            {
                 text: qsTr("退出")
                 onTriggered: Qt.quit()
            }
        }
    }

    Column {       
            width: 630
   
            Label {
                id: labelAdjust
                text: "调节器"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            
         
            Slider {
                id: slider_start_x 
                width: parent.width 
                height: 50
                from: 0
                to: 800
                value: 0
                onMoved: {
                    console.log("start_x value: " + value)
                    window.start_x= value
                    window.updateMat()
                }
            }
            
            Slider {
                id: slider_start_y
                width: parent.width 
                height: 50
                from: 0
                to: 800
                value: 0
                onMoved: {
                    console.log("start_y value: " + value)
                    window.start_y= value
                    window.updateMat()
                }
            }

            Slider {
                id: slider_shift
                width: parent.width 
                height: 50
                from: 0
                to: 10
                value: 5
                onMoved: {
                    console.log("shift value: " + value)
                    window.shift= value
                    window.updateMat()
                }
            }

            Slider {
                id: slider_thickness
                width: parent.width 
                height: 50
                from: 2
                to: 25
                value: 10
                onMoved: {
                    console.log("thickness value: " + value)
                    window.thickness = value
                    window.updateMat()
                }
            }

          Slider {
                id: slider_radius
                width: parent.width 
                height: 50
                from: 0
                to: 200
                value: 100
                onMoved: {
                    console.log("radius value: " + value)
                    window.radius = value
                    window.updateMat()
                }
            }
        }

        PaintItem {
                id: arrowImage
                text: "画Arrowline"
                x: 650
                y: 0
        }


        PaintItem {
            id: circleImage
            text: "画Circle"
            x: 0
            y: 430
        }
    
        PaintItem {
            id: lineImage
            text: "画clipLine"
            x: 650
            y: 430
        }
    
        Component.onCompleted: {
            arrowImage.image.setSource()
            circleImage.image.setSource()
            lineImage.image.setSource()
        }

        function updateMat() {
            arrowImage.image.drawArrowLine(arrowImage.image.mat, start_x, start_y, thickness, shift)
            circleImage.image.drawCircle(circleImage.image.mat, start_x, start_y, radius, thickness, shift)
            lineImage.image.drawLine(lineImage.image.mat, start_x, start_y, thickness)
        }
}