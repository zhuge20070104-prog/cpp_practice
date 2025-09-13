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
                    medianImage.image.medianMat(srcImage.image.mat)
                    gaussianImage.image.gaussianMat(srcImage.image.mat)
                    bilateralImage.image.bilateralMat(srcImage.image.mat)
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
            id: medianImage
            text: "Median Image"
            x: 650
            y: 0
        }

        PaintItem {
            id: gaussianImage
            text: "Gaussian Image"
            x: 0
            y: 440
        }

        PaintItem {
            id: bilateralImage
            text: "Bilateral Image"
            x: 650
            y: 440
        }
}