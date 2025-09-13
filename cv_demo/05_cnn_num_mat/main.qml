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

    property var kernel: "1 1\n1 1"
    property var src_mat: "1 2 5\n6 8 1\n0 1 2"

    width: 1400; height: 570
    menuBar: MenuBar
    {
        Menu
        {
            title: qsTr("文件")

            MenuItem
            {
                text: qsTr("更新Source Mat")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
                    dialog_src.show();
                    dialog_src.requestActivate();
                 }
            }
        
            MenuItem
            {
                text: qsTr("更新Kernel")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
                    dialog_kernel.show();
                    dialog_kernel.requestActivate();
                 }
            }

            MenuItem
            {
                text: qsTr("计算")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
                    cnnImage.image.cnnMat(srcImage.image.mat, kernel)
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
            id: srcImage
            text: "Source Image"
            x: 0
            y: 0
        }


        PaintItem {
            id: cnnImage
            text: "CNN Image"
            x: 650
            y: 0
        }

        Rectangle {
            x: 0

            y: 450
            
            width: 200
            height: 80
            Label {
                id: status_bar
                anchors.centerIn: parent
                anchors.fill: parent
                text:  "Kernel:\n"
             }
        }
      

        ValueDialog{
            id: dialog_kernel
            visible: false
            text: kernel
            onValueChanged: {
                console.log("value" )
                console.log(value)
                kernel = text 
                status_bar.text = "Kernel: \n" + kernel 
                cnnImage.image.cnnMat(srcImage.image.mat, kernel)
            }
        }

        ValueDialog{
            id: dialog_src
            visible: false
            text: src_mat
            onValueChanged: {
                console.log("value" )
                console.log(value)
                src_mat = text 
                srcImage.image.setSource(src_mat)
            }
        }

        Component.onCompleted: {
            srcImage.image.setSource(src_mat)
            status_bar.text = "Kernel: \n" + kernel 
        }
}