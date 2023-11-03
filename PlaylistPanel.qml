import QtQuick
import Qt5Compat.GraphicalEffects
import com.PlayerController

Rectangle {
    id: root

    signal searchRequested
    signal mouseClicked

    color: "#211b3f"
    radius: 20

    Text {
        id: playlistText
        anchors {
            left: parent.left
            top: parent.top
            margins: 25
        }

        text: "Playlist"
        color: "white"
        font {
            pixelSize: 25
        }
    }

    ImageButton {
        width: 30
        height: 30
        source: "assets/icons/add-btn.png"
        anchors {
            right: parent.right
            top: parent.top
            margins: 25
        }

        onClicked: root.searchRequested()
    }

    Rectangle {
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "#6e0ab8"
            }
            GradientStop {
                position: 0.6
                color: "#C200FF"
            }
            GradientStop {
                position: 1.0
                color: "#F800F6"
            }
        }

        anchors {
            fill: parent
            topMargin: 80
            bottomMargin: 30
        }
        ListView {
            id: listView

            anchors {
                fill: parent
                margins: 20
            }

            model: PlayerController
            clip: true
            spacing: 10

            delegate: Rectangle {
                id: delegate

                required property int index
                required property string audioTitle
                required property string audioAuthor
                required property url audioImage
                required property url audioSource

                color: "#211b3f"

                height: 55
                width: listView.width

                Column {
                    id: textsColumn

                    anchors {
                        top: parent.top
                        left: parent.left
                        right: removeButton.left
                        margins: 5
                    }

                    spacing: 5

                    Text {
                        width: textsColumn.width
                        elide: Text.ElideRight
                        fontSizeMode: Text.Fit
                        minimumPixelSize: 10
                        color: "white"
                        text: delegate.audioTitle

                        font {
                            pixelSize: 16
                            bold: true
                        }
                    }

                    Text {
                        width: textsColumn.width
                        elide: Text.ElideRight
                        fontSizeMode: Text.Fit
                        minimumPixelSize: 6
                        color: "gray"
                        text: delegate.audioAuthor

                        font {
                            pixelSize: 12
                        }
                    }
                }
                MouseArea {
                    id: delegateMouseArea
                    anchors.fill: parent
                    onClicked: {
                        PlayerController.switchToSongByIndex(delegate.index)
                        root.mouseClicked()
                    }
                }

                ImageButton {
                    id: removeButton

                    anchors {
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                        rightMargin: 10
                    }

                    width: 30
                    height: 30

                    source: "assets/icons/delete-btn.png"

                    onClicked: {
                        PlayerController.removeAudio(delegate.index)
                    }
                }
            }
        }
    }
}
