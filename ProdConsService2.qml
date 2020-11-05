import QtQuick 2.15
import QtQuick.Controls 1.1
import com.mano.ProdConsService2 1.0

Rectangle {
    Component {
        id: contactDelegate
        Rectangle {
            id:cir_box;
            width: 50
            height: 50
            color: "white"
            border.color: "black"
            border.width: 1;
            Rectangle{
                id:cir;
                anchors.centerIn:cir_box.centerIn;
                opacity:0;
                visible:true;
                radius:width/2;
                transitions:[
                    Transition {
                        from: "*"; to: "show";
                        NumberAnimation {
                            properties: "opacity";
                            easing.type: Easing.InOutQuad;
                            duration: 400;
                        }
                    },
                    Transition {
                        from: "show"; to: "hidden";
                        NumberAnimation {
                            properties: "opacity";
                            easing.type: Easing.InOutQuad;
                            duration: 400;
                        }
                    }
                    
                ]
                color:'red';
                width:30;
                states: [
                    State {
                        name: "hidden";
                        PropertyChanges{target:cir;opacity:0.0;}
                    },
                    State {
                        name: "show";
                        PropertyChanges{target:cir;opacity:1.0;}
                    }
                ]
                height:30;
            }
        }
        
    }

    ListModel {
        id: contactModel
        ListElement {
            index:0;
        }
        ListElement {
            index:1;
        }
        ListElement {
            index:2
        }
        ListElement {
            index:3;
        }
        ListElement {
            index:4;
        }
        ListElement {
            index:5;
        }
        ListElement {
            index:6;
        }
        ListElement {
            index:7;
        }
        ListElement {
            index:8;
        }
        ListElement {
            index:9;
        }
    }

    ListView {
        id:listView;
        anchors.fill: parent
        model: contactModel
        orientation:ListView.Horizontal
        spacing:20
        delegate: contactDelegate
    }

    Button {
        id:btn
        text:"start"
        onClicked: () => {
                service.start();
        }
    }
    
    ProdConsService2 {
        id: service;
    }

    PropertyAnimation {
        id: prodAnima;
        target: box;
        property: "x";
        duration: 500;
        onStarted:()=>{
            service.lock_producer();

        }
        onFinished: () => {
            service.unlock_producer();
        }
    }
    PropertyAnimation {
        id: conAnima;
        target: box1;
        property: "x";
        duration: 500;
        onStarted:()=>{
            service.lock_consumer();

        }
        onFinished: () => {
            service.unlock_consumer();
        }
    }
    Rectangle {
        id:box
        width: 20; height: 20;
        opacity:0.5;
        y:160;
        color:'red';
    }
    Rectangle {
        id:box1
        width: 20; height: 20;
        y: 60;
        opacity:0.5;
        color:'blue';
    }
    Connections {
        target: service;
        // 消费时触发
        function onFrontChanged(index){
            // contactModel.set(index,{vis:false});
            let item = listView.itemAtIndex(index);
            item.children[0].state = 'hidden';
            conAnima.to = item.x;
            conAnima.start();
        }
        // 生产时触发
        function onRealChanged(index){
            // contactModel.set(index,{vis:true});
            let item = listView.itemAtIndex(index);
            item.children[0].state = 'show';
            prodAnima.to = item.x;
            prodAnima.start();
        }
    }

}