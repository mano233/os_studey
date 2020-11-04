import QtQuick 2.0
import QtQuick.Window 2.15
//import "./mybox"

Rectangle {
    id:window
    z:9;
    anchors.fill: parent;
    property bool finished: false

    function updatePos (item_orig, item_dest) {
       var pos_abs = window.mapFromItem (item_orig.parent, item_orig.x, item_orig.y);
       return window.mapToItem (item_dest.parent, pos_abs.x, pos_abs.y);
    }

    Rectangle{
            id: cir1;
            width: 50;
            opacity:0;
            height: 50;
            color:"red";
            z:9;
            SequentialAnimation{
                id:anim2

                running:true
                NumberAnimation{
                    target:cir1
                    properties:"opacity"
                    to:1
                    duration:400
                }
                NumberAnimation{
                    target:cir1
                    properties:"x"
                    to:updatePos (row, cir1).x+box2.x
                    duration:300
                    easing.type: Easing.InOutBack

                }
                onRunningChanged:{
                    if(!anim2.running){
                        cir1.x = Qt.binding(function() { return updatePos (row, cir1).x+box2.x;})

                        console.log("122312")
                    }
                }


            }
            radius:width/2;
    }  
    Row{
        id:row;
        x:100;
        Rectangle{
            id: box1
            width: 100
            height: 100
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    anima1.start()
                }
            }
            z:9
            Text{
                anchors.centerIn: parent
                text:"box1"
            }
            border.color: "black"
            border.width: 1
        }
        Rectangle{
            id: box2
            width: 100
            Text{
               anchors.centerIn: parent
                text:"box2"
            }
            height: 100
            z:9
            border.color: "black"
            border.width: 1
        }
        Rectangle{
            id: box3
            width: 100
             Text{
                 anchors.centerIn: parent
                text:"box3"
            }
            height: 100
            z:9
            border.color: "black"
            border.width: 1
        }
         Rectangle{
            id: box4
            width: 100
             Text{
                 anchors.centerIn: parent
                text:"box4"
            }
            height: 100
            z:9
            border.color: "black"
            border.width: 1
        }
        NumberAnimation on x {
            id:anima1
            from: 0
            running:false
            to: 360
        }
        
    }
}