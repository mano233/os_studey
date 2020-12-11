//import QtQuick 2.0
//import QtQuick.Window 2.15
//import QtQuick.Controls 2.15

import QtQuick
import QtQuick.Controls
import QtQuick.Window

Window {
    visible: true
    width: 800
    height: 480
    color: 'black'

    ShaderEffect {
        id: effect

        readonly property vector3d defaultResolution: Qt.vector3d(width, height, width / height)
        //pass
        readonly property vector3d iResolution: defaultResolution
        property real iTime: 0
        property real iTimeDelta: 100
        property int iFrame: 10
        property real iFrameRate
        property vector4d iMouse
        property var iChannel0 //only Image or ShaderEffectSource
        property var iChannel1 //only Image or ShaderEffectSource
        property var iChannel2 //only Image or ShaderEffectSource
        property var iChannel3 //only Image or ShaderEffectSource
        property var iChannelTime: [0, 1, 2, 3]
        property var iChannelResolution: [calcResolution(iChannel0), calcResolution(iChannel1), calcResolution(iChannel2), calcResolution(iChannel3)]
        property vector4d iDate
        property real iSampleRate: 44100

        function calcResolution(channel) {
            if (channel)
                return Qt.vector3d(channel.width, channel.height, channel.width / channel.height);
            else
                return defaultResolution;
        }

        anchors.fill: parent
        fragmentShader: "qrc:/heart.frag.qsb"

        Timer {
            running: true
            triggeredOnStart: true
            interval: 1
            repeat: true
            onTriggered: {
                effect.iTime += 0.001;
            }
        }

    }

    Text {
        text: 'demo'
        color: 'red'
    }

}
