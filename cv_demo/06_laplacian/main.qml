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


    width: 1400; height: 1000
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
                text: qsTr("处理")
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
            id: sobelImage
            text: "Sobel Image"
            x: 650
            y: 0
        }

        PaintItem {
            id: lapImage
            text: "Laplacian Image"
            x: 0
            y: 460
        }

        function updateMat() {
            sobelImage.image.sobelMat(srcImage.image.mat, 1, 1, 1, 1, 1)
            lapImage.image.laplacianMat(srcImage.image.mat, 1, 1)
        }
}