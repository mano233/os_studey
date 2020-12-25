import QtGraphicalEffects
import QtQuick
import QtQuick.Controls
import QtQuick.Controls
import QtQuick.Window

Window {
    id: root

    visible: true
    width: 800
    height: 480

    Rectangle {
        id: r
        color:'blue'
        width: 200
        height: 100
        Row {
            Item {
                id: foo

                width: 100
                height: 100
                clip: true

                Image {
                    source: "file:/Users/mano233/Documents/c_projects/untitled3/tex.png"
                    z: 0
                }

                Rectangle {
                    x: 5
                    y: 5
                    width: 60
                    height: 60
                    color: "red"
                }

                Rectangle {
                    x: 20
                    y: 20
                    width: 60
                    height: 60
                    color: "orange"
                }

                Rectangle {
                    x: 35
                    y: 35
                    width: 60
                    opacity: 0.5
                    height: 60
                    color: "yellow"
                }

            }
        }



        Dial {
            id:dial
        }

    }
 FastBlur {
            width: 200
            height: 100
            source: r
            radius: dial.value*100
            x:200
        }
}
