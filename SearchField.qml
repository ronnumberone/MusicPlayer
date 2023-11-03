import QtQuick

Rectangle {
    id: root

    signal accepted(string value)

    color: "#211b3f"

    TextInput {
        id: searchInput

        anchors.fill: parent

        font.pixelSize: 14
        color: "white"
        leftPadding: 30
        verticalAlignment: TextInput.AlignVCenter

        Image {
            anchors {
                left: parent.left
                leftMargin: 5
                verticalCenter: parent.verticalCenter
            }

            width: 16
            height: 16

            mipmap: true
            source: "assets/icons/search-btn.png"
        }

        onAccepted: {
            root.accepted(text)
        }
    }
}
