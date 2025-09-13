import QtQuick 2.12
import QtQuick.Controls 2.4
import Qt.labs.platform 1.1 as NativeDialogs

ApplicationWindow {
    id: root 

    width: 640
    height: 480

    title: (file_name.length === 0? qsTr("Document"): file_name + (is_dirty?"*":""))
    property bool is_dirty: true 
    property string file_name
    property bool trying_to_close: false

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&New")
                icon.name: "document-new"
                onTriggered: root.newDocument()
            }
            MenuSeparator {}

            MenuItem {
                text: qsTr("&Open")
                icon.name: "document-open"
                onTriggered: root.openDocument()
            }

            MenuItem {
                text: qsTr("&Save")
                icon.name: "document-save"
                onTriggered: root.saveDocument() 
            }

            MenuItem {
                text: qsTr("Save &As...")
                icon.name: "document-save-as"
                onTriggered: root.saveAsDocument()
            }
        }
    }

    function _createNewDocument() {
        var component = Qt.createComponent("DocumentWindow.qml")
        var window = component.createObject()
        return window
    }

    function newDocument() {
        var window = _createNewDocument()
        window.show()
    }

    function openDocument(file_name) {
        openDialog.open()
    }

    function saveAsDocument() {
        saveAsDialog.open()
    }

    function saveDocument() {
        if(file_name.length === 0) {
            root.saveAsDocument()
        } else {
            console.log("Saving document")
            root.is_dirty = false 
            if(root.trying_to_close) {
                root.close()
            }
        }
    }

    NativeDialogs.FileDialog {
        id: openDialog
        title: "Open"
        folder: NativeDialogs.StandardPaths.writableLocation(NativeDialogs.StandardPaths.DocumentsLocation)
        onAccepted: {
            var window = root._createNewDocument()
            window.file_name = openDialog.file 
            window.show()
        }
    }


    NativeDialogs.FileDialog {
        id: saveAsDialog
        title: "Save As"
        folder: NativeDialogs.StandardPaths.writableLocation(NativeDialogs.StandardPaths.DocumentsLocation)

        onAccepted: {
            root.file_name = saveAsDialog.file 
            saveDocument()
        }

        onRejected: {
            root.trying_to_close = false
        }
    }

    NativeDialogs.MessageDialog {
        id: closeWarningDialog 
        title: "Closing document"
        text: "You have unsaved changes. Do you want to save your changes?"
        buttons: NativeDialogs.MessageDialog.Yes | NativeDialogs.MessageDialog.No | NativeDialogs.MessageDialog.Cancel
        onYesClicked:  {
            root.trying_to_close = true 
            root.saveDocument()
        }
        onNoClicked: {
            root.is_dirty = false 
            root.close()
        }
        onRejected: {

        }
    }

    onClosing: {
        if(root.is_dirty) {
            closeWarningDialog.open()
            close.accepted = false
        }
    }
  
}