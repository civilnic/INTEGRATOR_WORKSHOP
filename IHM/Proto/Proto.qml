import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    id:main_window
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
                iconSource: "images/icons/ic_chevron_left_black_48dp.png"
                onClicked: main_window.color="blue"
            }
            ToolButton {
                height:50
                width:parent.width
                iconSource: "images/icons/ic_chevron_right_black_48dp.png"
                onClicked: main_window.color="#9b9696"
            }
        }


    }

    statusBar: StatusBar{
        RowLayout {
            anchors.fill: parent
            width:parent.width

               Text{
                   text:qsTr("En cours de dev")
                }

        }
    }

    SplitView {
        TableView{
            height:parent.height
            TableViewColumn{
                width:20

                title: "Models"
                role:  "name"
            }
            model: 20
        }
        Rectangle{
            color: "blue"
        }
    }
}
