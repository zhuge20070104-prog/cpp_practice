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

    property var kernel: "-1 1 -1\n1 1 1\n-1 1 -1"

    width: 1400; height: 570
    menuBar: MenuBar
    {
        Menu
        {
            title: qsTr("文件")
            MenuItem
            {
                 text: qsTr("打开文件")
                icon.name: "document-open"
                 onTriggered:
                 {
                     fileOpenDialog.open()
                 }
            }

            MenuItem
            {
                text: qsTr("更新Kernel")
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
 
    FileDialog {
        id: fileOpenDialog
        title: "Select an image file"
        folder: shortcuts.documents
        nameFilters: [
            "Image Files (*.png *.jpeg *.jpg *.webp)"
        ]
        onAccepted: {
            srcImage.image.setSource(fileOpenDialog.fileUrl)
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
            id: dialog
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

        Component.onCompleted: {
            status_bar.text = "Kernel: \n" + kernel 
        }
}