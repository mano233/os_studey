//import QtQuick 2.0
//import QtQuick.Window 2.15
//import QtQuick.Controls 2.15

import QtQuick
import QtQuick.Window
import QtQuick.Controls
Window{
    visible: true
    width: 800
    id: root
    height: 480
    Button {
        text:"start"
        onClicked: {
            var component = Qt.createComponent("qrc:/qml/qml02.qml")
            var window    = component.createObject(root)
            // window.modality = Qt.WindowModal
            window.show()
        }
    }
}