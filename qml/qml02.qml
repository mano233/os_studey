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
    Rectangle{
            width:100;height:100;
            color:'red'
            RotationAnimation on rotation{
                from: 0
                loops: Animation.Infinite
                to: 360
                duration: 400
            }
        }
}