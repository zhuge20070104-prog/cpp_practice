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

    property var is_closed: 1
    width: 1300; height: 700
    menuBar: MenuBar
    {
        Menu
        {
            title: qsTr("绘制")
            MenuItem
            {
                text: qsTr("画Contours")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
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

    PaintItem {
            id: contourImage1
            text: "Contours1"
            x: 0
            y: 0
    }


    PaintItem {
        id: contourImage2
        text: "Contours2"
        x: 650
        y: 0
    }


    Component.onCompleted: {
        contourImage1.image.setSource()
        contourImage2.image.setSource()
        window.updateMat()
    }

    function updateMat() {
        contourImage1.image.drawContour1(contourImage1.image.mat)
        contourImage2.image.drawContour2(contourImage2.image.mat)
    }
}