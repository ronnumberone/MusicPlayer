import QtQuick
import Qt5Compat.GraphicalEffects
import QtQuick.Controls
import com.PlayerController

Slider {
    id: root
    property bool hidden: true
    property color checkedColor: "#e001fe"

    height: 3
    from: 0
    to: 100
    value: 100
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
    onValueChanged: {
        PlayerController.changeVolume(Math.round(value))
    }
}
