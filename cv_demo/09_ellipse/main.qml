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

    property var c_width: 85
    property var c_height: 85
    property var angle: 0
    property var start_angle: 0
    property var end_angle: 360

    width: 1500; height: 1000
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
                id: slider_width
                width: parent.width 
                height: 50
                from: 0
                to: 150
                value: 85
                onMoved: {
                    console.log("width value: " + value)
                    window.c_width= value
                    window.updateMat()
                }
            }
            
            Slider {
                id: slider_height
                width: parent.width 
                height: 50
                from: 0
                to: 150
                value: 85
                onMoved: {
                    console.log("height value: " + value)
                    window.c_height= value
                    window.updateMat()
                }
            }

            Slider {
                id: slider_angle
                width: parent.width 
                height: 50
                from: 0
                to: 360
                value: 0
                onMoved: {
                    console.log("angle value: " + value)
                    window.angle= value
                    window.updateMat()
                }
            }

            Slider {
                id: slider_start_angle
                width: parent.width 
                height: 50
                from: 0
                to: 360
                value: 0
                onMoved: {
                    console.log("start_angle value: " + value)
                    window.start_angle = value
                    window.updateMat()
                }
            }

          Slider {
                id: slider_end_angle
                width: parent.width 
                height: 50
                from: 0
                to: 360
                value: 360
                onMoved: {
                    console.log("end_angle value: " + value)
                    window.end_angle = value
                    window.updateMat()
                }
            }
        }

        PaintItem {
                id: circleImage
                text: "画圆"
                x: 650
                y: 0
        }


        PaintItem {
            id: circleImage1
            text: "画圆1"
            x: 0
            y: 430
        }
    
        PaintItem {
            id: ellip2PolyImage
            text: "Ellipse2Poly"
            x: 650
            y: 430
        }
    
        Component.onCompleted: {
            circleImage.image.setSource()
            circleImage1.image.setSource()
            ellip2PolyImage.image.setSource()
        }

        function updateMat() {
            circleImage.image.drawCircle(circleImage.image.mat, c_width, c_height,  angle, start_angle, end_angle)
            circleImage1.image.drawCircle1(circleImage1.image.mat, angle)
            ellip2PolyImage.image.drawE2Polly(ellip2PolyImage.image.mat)
        }
}