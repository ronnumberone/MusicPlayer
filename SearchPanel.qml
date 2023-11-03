import QtQuick
import Qt5Compat.GraphicalEffects
import com.PlayerController
import com.AudioSearchModel

Rectangle {
    id: root

    property bool hidden: true

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

    ListView {
        id: listView

        anchors {
            fill: parent
            margins: 20
        }

        spacing: 10
        clip: true
        model: AudioSearchModel
        visible: !AudioSearchModel.isSearching

        delegate: Rectangle {
            id: delegate

            required property string audioTitle
            required property string audioAuthor
            required property url audioSource
            required property url audioImage
            required property int index

            width: listView.width
            height: 50

            color: "#211b3f"

            Image {
                id: audioImage

                anchors {
                    left: parent.left
                    leftMargin: 5
                    verticalCenter: parent.verticalCenter
                }

                width: 32
                height: 32

                source: delegate.audioImage
            }

            Column {
                anchors {
                    left: audioImage.right
                    right: parent.right
                    top: parent.top

                    margins: 5
                }

                spacing: 5

                Text {
                    width: parent.width

                    text: delegate.audioTitle
                    color: "white"

                    fontSizeMode: Text.Fit
                    minimumPixelSize: 12
                    elide: Text.ElideRight

                    font {
                        pixelSize: 16
                        bold: true
                    }
                }

                Text {
                    width: parent.width

                    text: delegate.audioAuthor
                    color: "gray"

                    fontSizeMode: Text.Fit
                    minimumPixelSize: 8
                    elide: Text.ElideRight

                    font {
                        pixelSize: 12
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.hidden = true
                    PlayerController.addAudio(delegate.audioTitle,
                                              delegate.audioAuthor,
                                              delegate.audioImage,
                                              delegate.audioSource)
                }
            }
        }
    }

    Text {
        anchors.centerIn: parent

        color: "#211b3f"
        visible: AudioSearchModel.isSearching || listView.count === 0
        text: if (AudioSearchModel.isSearching) {
                  return "Searching..."
              } else if (listView.count === 0) {
                  return "No results"
              } else {
                  return ""
              }

        font {
            pixelSize: 28
            bold: true
        }
    }

    Behavior on y {
        PropertyAnimation {
            easing.type: Easing.InOutQuad
            duration: 200
        }
    }
}
