import QtQuick 2.12
import Qt.labs.platform 1.1
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.2



ApplicationWindow
{
    visible: true
    title: qsTr("OpenCV图像处理助手")
    color:"#FFFFFF"
    x:0
    y:0
    width: 1400; height: 1300
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
                text: qsTr("更新Mat")
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
            id: erodeRecImage
            text: "Erode Image"
            x: 650
            y: 0
        }

        PaintItem {
            id: dilateRecImage
            text: "Dilate Image"
            x: 0
            y: 440
        }

        PaintItem {
            id: tidyImage
            text: "Tidy Image"
            x: 650
            y: 440
        }

        ValueDialog{
            id: dialog
            text: "11"
            visible: false

            onValueChanged: {
                console.log("value" )
                console.log(value)
                var kernel_size = parseInt(value)

                erodeRecImage.image.erodeMat(srcImage.image.mat, kernel_size)
                dilateRecImage.image.dilateMat(srcImage.image.mat, kernel_size)
                tidyImage.image.tidyMat(srcImage.image.mat, kernel_size)
               
            }
        }
}