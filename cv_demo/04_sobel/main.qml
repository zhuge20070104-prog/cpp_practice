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

    property var dx: 0
    property var dy: 1
    property var kernel_size: 3
    property var scale_factor: 1
    property var delta_value: 1

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
                text: qsTr("更新dx, dy")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
                    dialog.show();
                    dialog.requestActivate();
                 }
            }

            MenuItem
            {
                text: qsTr("增加sobel kernel")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
                    kernel_size += 2
                    window.updateMat()
                    window.updateStatusBarText()  
                 }
            }

            MenuItem
            {
                text: qsTr("减少sobel kernel")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
                    if(kernel_size > 1) {
                        kernel_size -= 2
                    }
                    window.updateMat()
                    window.updateStatusBarText()  
                 }
            }

            MenuItem
            {
                text: qsTr("增加scaleFactor")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
                    scale_factor += 1
                    window.updateMat()
                    window.updateStatusBarText()  
                 }
            }

            MenuItem
            {
                text: qsTr("减少scaleFactor")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
                    if(scale_factor >1) {
                        scale_factor -= 1
                    }

                    window.updateMat()
                    window.updateStatusBarText()  
                 }
            }



            MenuItem
            {
                text: qsTr("增加deltaValue")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
                    delta_value += 1
                    window.updateMat()
                    window.updateStatusBarText()  
                 }
            }

            MenuItem
            {
                text: qsTr("减少deltaValue")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
                    if(delta_value > 1) {
                        delta_value -= 1
                    }
                    window.updateMat()
                    window.updateStatusBarText()  
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
            sobelImage.image.setSource(fileOpenDialog.fileUrl)
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

        Rectangle {
            x: 0

            y: 450
            
            width: 200
            height: 30
            Label {
                id: status_bar
                anchors.centerIn: parent
                anchors.fill: parent
                text:  "HAHA"
             }
        }
      

        ValueDialog{
            id: dialog
            currentIndex: 1
            visible: false

            onValueChanged: {
                console.log("value" )
                console.log(value)
                dx = parseInt(value)

                if(dx === 0) {
                    dy = 1
                } else {
                    dy = 0
                }

                print("dx" + dx)
                print("dy" + dy)
                window.updateMat()
                window.updateStatusBarText()
            }
        }

        function updateStatusBarText() {
            status_bar.text = "dx: " + dx + ", dy: " + dy + ", kenel_size: " + kernel_size + ", scale_factor: " +
                 scale_factor +", delta_value: " + delta_value;
        }

        function updateMat() {
            sobelImage.image.sobelMat(srcImage.image.mat, dx, dy, kernel_size, scale_factor, delta_value)
        }
        Component.onCompleted: {
           window.updateStatusBarText()
        }
}