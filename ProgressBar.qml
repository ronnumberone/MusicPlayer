import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import com.PlayerController

Slider {
    id: root
    from: 0
    height: 3
    to: PlayerController.duration()
    property color checkedColor: "#e001fe"

    background: Rectangle {
        x: root.leftPadding
        y: root.topPadding + root.availableHeight / 2 - height / 2
        implicitWidth: 200
        implicitHeight: 3
        width: root.availableWidth
        height: implicitHeight
        radius: height / 2
        color: "#5c62b1"

        Rectangle {
            width: root.visualPosition == 0 ? 0 : root.handle.x + root.handle.width / 2
            height: parent.height
            color: root.checkedColor
            radius: height / 2

            layer.enabled: root.hovered | root.pressed
            layer.effect: DropShadow {
                transparentBorder: true
                color: root.checkedColor
                samples: 8
            }
        }
    }

    handle: Rectangle {
        x: root.leftPadding + root.visualPosition * (root.availableWidth - width)
        y: root.topPadding + root.availableHeight / 2 - height / 2
        implicitWidth: root.background.implicitHeight + 6
        implicitHeight: implicitWidth
        radius: implicitWidth / 2
        color: root.pressed ? Qt.darker(root.checkedColor,
                                        1.2) : root.checkedColor
        border.color: Qt.darker(root.checkedColor, 0.93)

        layer.enabled: root.hovered | root.pressed
        layer.effect: DropShadow {
            transparentBorder: true
            color: root.checkedColor
            samples: 10 /*20*/
        }
    }

    Timer {
        interval: 100 // Cập nhật mỗi 100 milliseconds
        running: PlayerController.isPlaying // Chỉ hoạt động khi bài hát đang phát
        repeat: true

        onTriggered: {
            if (PlayerController.duration() > 0) {
                value = PlayerController.currentPosition()
            }
        }
    }

    onValueChanged: {
        if (value >= PlayerController.duration()) {
            if (PlayerController.isLooping) {
                PlayerController.loopSong()
            } else {
                PlayerController.switchToNextSong()
            }
            value = 0
            to = PlayerController.duration()
        }
    }

    // Khi giá trị của slider thay đổi
    onMoved: {
        // Nếu slider không được nhấn, cập nhật vị trí của bài hát
        PlayerController.setCurrentPosition(value)
    }
}
