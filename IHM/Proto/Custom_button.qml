import QtQuick 2.0

BorderImage {
    id:bouton_toto
    width:15
    height:7
    property alias bouton_text: champ.text
    source:"images/button_light.png"

    border.left:4
    border.right: 4
    border.bottom: 4
    border.top:4

    Text {
        id:champ
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment:  Text.AlignVCenter
        anchors.margins:10
        font.pixelSize: 14
        text:qsTr("Open")
    }

}
