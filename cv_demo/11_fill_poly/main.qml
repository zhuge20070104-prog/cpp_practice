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
    width: 1400; height: 1000
    menuBar: MenuBar
    {
        Menu
        {
            title: qsTr("绘制")
            MenuItem
            {
                text: qsTr("画Polygon")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
                    dialog.show();
                    dialog.requestActivate();
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
            id: conveyPolyImage
            text: "fillConvexPoly"
            x: 0
            y: 0
    }


    PaintItem {
        id: polyImage
        text: "fillPoly"
        x: 650
        y: 0
    }

    PaintItem {
        id: polyLineImage
        text: "polylines"
        x: 0
        y: 420
    }

    ValueDialog{
            id: dialog
            currentIndex: 1
            visible: false

            onValueChanged: {
                console.log("value" )
                console.log(value)
                is_closed = parseInt(value)
                console.log("is_closed: " + is_closed)
                window.updateMat()
            }
    }

    Component.onCompleted: {
        conveyPolyImage.image.setSource()
        polyImage.image.setSource()
        polyLineImage.image.setSource()
        window.updateMat()
    }

    function updateMat() {
        conveyPolyImage.image.drawConvexPoly(conveyPolyImage.image.mat)
        polyImage.image.drawPoly(polyImage.image.mat)
        polyLineImage.image.drawPolyLines(polyLineImage.image.mat, is_closed)
    }
}