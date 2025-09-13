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

    property var top_left_pos: 10.0
    property var bottom_right_pos: 50.0

    width: 700; height: 500
    menuBar: MenuBar
    {
        Menu
        {
            title: qsTr("绘制")
            MenuItem
            {
                text: qsTr("画矩形")
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
            Slider {
                id: slider_left_top
                width: parent.width 
                height: 50
                from: 10
                to: 330
                onMoved: {
                    console.log("Left top value: " + value)
                    window.top_left_pos = value
                    window.updateMat()
                }
            }
            
            Slider {
                id: slider_right_bottom
                width: parent.width 
                height: 50
                from: 10
                to: 330
                value: 50
                onMoved: {
                    console.log("Right Bottom value: " + value)
                    window.bottom_right_pos = value
                    window.updateMat()
                }
            }
            PaintItem {
                id: srcImage
                text: "画矩形"
                x: 0
                y: 0
             }
        }
 
    
        Component.onCompleted: {
            srcImage.image.setSource()
        }
        function updateMat() {
            srcImage.image.drawRect(srcImage.image.mat, top_left_pos, bottom_right_pos)
        }
}