import QtQuick
import com.PlayerController

Item {
    id: root

    Image {
        id: albumImage
        width: 169
        height: 169
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.verticalCenter
        }
        source: !!PlayerController.currentSong ? PlayerController.currentSong.audioImage : ""
    }

    Text {
        id: titleText
        anchors {
            left: parent.left
            right: parent.right
            top: albumImage.bottom
            topMargin: 35
        }

        color: "white"
        text: !!PlayerController.currentSong ? PlayerController.currentSong.audioTitle : ""
        horizontalAlignment: Text.AlignHCenter

        font {
            pixelSize: 25
        }
    }

    Text {
        id: authorText
        anchors {
            left: parent.left
            right: parent.right
            top: titleText.bottom
            topMargin: 10
        }
        text: !!PlayerController.currentSong ? PlayerController.currentSong.audioAuthor : ""
        horizontalAlignment: Text.AlignHCenter

        color: "white"

        font {
            pixelSize: 15
        }
    }
}
