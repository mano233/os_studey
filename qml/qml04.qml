//import QtQuick 2.0
//import QtQuick.Window 2.15
//import QtQuick.Controls 2.15

import QtQuick
import QtQuick.Window
import QtQuick.Controls
Window{
    visible: true
    width: 800
    height: 480

    ShaderEffect{
        id: effect
        anchors.fill: parent
        property real iTime: 0
        fragmentShader: "qrc:/lighting.frag.qsb"
        Timer{
            running: true
            triggeredOnStart: true
            interval: 10
            repeat: true
            onTriggered: {
                effect.iTime +=0.01;
            }
        }
    }
    Text{
        text:'demo'
        color:'red'
    }
}