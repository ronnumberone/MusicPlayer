import QtQuick
import QtQuick.Window
import Qt5Compat.GraphicalEffects
import com.PlayerController
import com.AudioSearchModel

Window {
    width: 820
    height: 600
    visible: true
    title: qsTr("Music Player")
    color: "#995CFF"

    MouseArea {
        anchors.fill: parent
        onClicked: volumeBar.hidden = true
    }

    Rectangle {
        id: leftBody
        color: "#211b3f"
        radius: 20
        clip: true

        enabled: !!PlayerController.currentSong

        anchors {
            right: parent.horizontalCenter
            left: parent.left
            top: parent.top
            bottom: parent.bottom
            topMargin: 50
            bottomMargin: 50
            leftMargin: 50
            rightMargin: -10
        }

        layer.enabled: true
        layer.effect: DropShadow {
            horizontalOffset: 15
            verticalOffset: 15
            radius: 8.0
            color: "#22000000"
            spread: 0.2
        }

        Rectangle {
            id: circle
            radius: 150
            height: parent.height - 250
            y: -50
            anchors {
                left: parent.left
                right: parent.right
                leftMargin: 35
                rightMargin: 35
            }

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
        }

        AudioInfoBox {
            id: songInfo
            anchors {
                left: parent.left
                right: parent.right
                verticalCenter: parent.verticalCenter
            }
        }

        ProgressBar {
            id: songProgressBar
            width: parent.width - 130

            anchors {
                horizontalCenter: parent.horizontalCenter
                bottom: controlButtons.top
                bottomMargin: 20
            }
        }

        ImageButton {
            id: volumeButton
            width: 18
            height: 18
            source: "assets/icons/volume-btn.png"

            anchors {
                right: songProgressBar.right
                bottom: songProgressBar.top
                margins: 10
            }
            onClicked: {
                volumeBar.hidden = !volumeBar.hidden
            }
        }

        VolumeBar {
            id: volumeBar
            visible: !hidden
            width: 70
            rotation: -90

            anchors {
                bottom: volumeButton.top
                horizontalCenter: volumeButton.horizontalCenter
                bottomMargin: 38
            }
        }

        Row {
            id: controlButtons

            anchors {
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
                bottomMargin: 30
            }

            spacing: 20

            ImageButton {
                id: loopButton

                width: 20
                height: 20

                anchors.verticalCenter: parent.verticalCenter

                source: PlayerController.isLooping ? "assets/icons/loop-enabled-btn.png" : "assets/icons/loop-disabled-btn.png"

                onClicked: {
                    PlayerController.activeLoop()
                }
            }

            ImageButton {
                id: previousButton

                width: 20
                height: 20

                anchors.verticalCenter: parent.verticalCenter

                source: "assets/icons/previous-btn.png"

                onClicked: {
                    songProgressBar.value = 0
                    PlayerController.switchToPreviousSong()
                    songProgressBar.to = PlayerController.duration()
                }
            }

            ImageButton {
                id: playPauseButton

                width: 50
                height: 50

                source: PlayerController.isPlaying ? "assets/icons/pause-btn.png" : "assets/icons/play-btn.png"

                onClicked: PlayerController.playPause()
            }

            ImageButton {
                id: nextButton

                width: 20
                height: 20

                anchors.verticalCenter: parent.verticalCenter

                source: "assets/icons/next-btn.png"
                clip: false

                onClicked: {
                    songProgressBar.value = 0
                    PlayerController.switchToNextSong()
                    songProgressBar.to = PlayerController.duration()
                }
            }

            ImageButton {
                id: randomButton

                width: 20
                height: 20

                anchors.verticalCenter: parent.verticalCenter

                source: PlayerController.isRandom ? "assets/icons/random-enabled-btn.png" : "assets/icons/random-disabled-btn.png"
                clip: false

                onClicked: {
                    PlayerController.randomSong()
                }
            }
        }
    }

    Item {
        id: rightBody
        anchors {
            right: parent.right
            left: parent.horizontalCenter
            top: parent.top
            bottom: parent.bottom
            margins: 50
        }

        Rectangle {
            id: slogan

            color: "#a575f7"
            radius: 30
            height: 50

            anchors {
                left: parent.left
                right: parent.right
            }

            Text {
                text: "Enjoy the music"
                color: "#c9c9c9"

                anchors {
                    centerIn: parent
                }

                font {
                    bold: true
                    pixelSize: 20
                }
            }

            layer.enabled: true
            layer.effect: DropShadow {
                horizontalOffset: 15
                verticalOffset: 15
                radius: 8.0
                color: "#20000000"
                spread: 0.2
            }
        }

        PlaylistPanel {
            id: playlistPanel
            anchors {
                top: slogan.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                topMargin: 30
            }

            onSearchRequested: {
                searchPanel.hidden = false
            }

            onMouseClicked: {
                songProgressBar.value = 0
                songProgressBar.to = PlayerController.duration()
            }
        }
    }
    SearchField {
        id: searchField
        height: 40
        anchors {
            left: parent.left
            right: parent.right
        }

        onAccepted: value => {
                        AudioSearchModel.searchSong(value)
                    }

        visible: !searchPanel.hidden

        ImageButton {
            id: closeSearchButton

            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
                rightMargin: 20
            }

            height: 32
            width: 32

            source: "assets/icons/cancel-btn.png"
            visible: !searchPanel.hidden

            onClicked: {
                searchPanel.hidden = true
            }
        }
    }

    SearchPanel {
        id: searchPanel
        anchors {
            left: parent.left
            right: parent.right
        }

        height: parent.height

        y: hidden ? parent.height : searchField.height
    }
}
