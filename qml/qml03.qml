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
    Rectangle {
        id: gradientRect;
        width: 10
        height: 10
        gradient: Gradient {
            GradientStop { position: 0; color: "white" }
            GradientStop { position: 1; color: "steelblue" }
        }
        visible: false; // should not be visible on screen.
        layer.enabled: true;
        layer.smooth: true
     }
     Text {
        id: textItem
        font.pixelSize: 48
        text: "Gradient Text"
        anchors.centerIn: parent
        layer.enabled: true
        // This item should be used as the 'mask'
        layer.samplerName: "maskSource"
        layer.effect: ShaderEffect {
            property var colorSource: gradientRect;
            fragmentShader: "qrc:/mask.frag.qsb"
        }
    }
}