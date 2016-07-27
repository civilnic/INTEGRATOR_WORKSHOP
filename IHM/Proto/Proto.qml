import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    width: 640
    color: "#9b9696"
    height: 480
    title: qsTr("Integrator Workshop")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    toolBar: ToolBar {

        RowLayout {
            anchors.fill: parent

            ToolButton {
                height:50
                width:parent.width
                text:"Open"
                iconSource: "images/button.png"
            }

        }


    }

    statusBar: StatusBar{

    }

    MainForm {
        anchors.fill: parent
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
