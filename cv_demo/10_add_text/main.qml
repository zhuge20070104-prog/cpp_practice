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

    width: 630; height: 490
    menuBar: MenuBar
    {
        Menu
        {
            title: qsTr("绘制")
            MenuItem
            {
                text: qsTr("画文本")
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
        width: 640
        PaintItem {
            id: putTextImage
            text: "PutText"
            x: 0
            y: 0
        }

        Label {
            id: ftSize_label
            text: "Size: "
            anchors.horizontalCenter: parent.horizontalCenter
        }

    }




    Component.onCompleted: {
        putTextImage.image.setSource()
    }

    function updateMat() {
        var ft_size = putTextImage.image.putText(putTextImage.image.mat)
        print(ft_size.width)
        print(ft_size.height)
        ftSize_label.text = "Size: width " + ft_size.width + ", height: " + ft_size.height
    }
}