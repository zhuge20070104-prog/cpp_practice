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

    property var pic_width: 640
    property var pic_height: 100
    property var width_ratio: 2
    property var height_ratio: 10

    width: 1400; height: 980
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
                text: qsTr("更新width, height")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
                    wh_dialog.show();
                    wh_dialog.requestActivate();
                 }
            }

            MenuItem
            {
                text: qsTr("更新宽高比")
                icon.source: "images/process.svg"
                 onTriggered:
                 {
                    wh_ratio_dialog.show()
                    wh_ratio_dialog.requestActivate()
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
            id: whImage
            text: "Width Height Image"
            x: 650
            y: 0
        }
            
        PaintItem {
            id: whRatioImage
            text: "Width Height Ratio Image"
            x: 0
            y: 450
        }

        Rectangle {
            x: 650

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
            id: wh_dialog
            width_text:  pic_width
            height_text: pic_height
            visible: false

            onValueChanged: {
                console.log("width: " + width_v )
                console.log("height: " + height_v)
                pic_width = parseInt(width_v)
                pic_height = parseInt(height_v)
                window.updateMat()
                window.updateStatusBarText()
            }
        }


        ValueDialog{
            id: wh_ratio_dialog
            width_text:  width_ratio
            height_text: height_ratio
            visible: false

            onValueChanged: {
                console.log("width ratio: " + width_v )
                console.log("height ratio: " + height_v)
                width_ratio = parseInt(width_v)
                height_ratio = parseInt(height_v)
                window.updateMat()
                window.updateStatusBarText()
            }
        }

        function updateStatusBarText() {
            status_bar.text = "Pic width: " + pic_width + ", Pic height: " + pic_height + "\nwidth ratio: " + width_ratio + ", height ratio: " +
                height_ratio;
        }

        function updateMat() {
            whImage.image.resizelMatWH(srcImage.image.mat, pic_width, pic_height)
            whRatioImage.image.resizelMatWHRatio(srcImage.image.mat, width_ratio, height_ratio)
        }
        
        Component.onCompleted: {
           window.updateStatusBarText()
        }
}