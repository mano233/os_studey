import QtQuick
import QtQuick.Controls

import com.mano.ProdConsService2 1.0

Rectangle {
    component Box_s:Rectangle{
        width: 50;height: 50;
        color: "white"
        border.color: "black"
        border.width: 1;
        Rectangle{
            id:cir;
            x:10;y:10;
            opacity:0;
            radius:width/2;
            color:'red';width:30;height:30;
            transitions:[
                    Transition {
                        from: "*"; to: "show";
                        NumberAnimation {
                            property: "opacity";
                            easing.type: Easing.InOutQuad;
                            duration: 400;
                        }
                    },
                    Transition {
                        from: "show"; to: "hidden";
                        NumberAnimation {
                            property: "opacity";
                            easing.type: Easing.InOutQuad;
                            duration: 400;
                        }
                        ColorAnimation {
                            property: "color";
                            easing.type: Easing.InOutQuad;
                            duration: 200;
                        }
                    }
                    
                ]
            states: [
                    State {
                        name: "hidden";
                        PropertyChanges{target:cir;opacity:0.0;color:'blue'}
                    },
                    State {
                        name: "show";
                        PropertyChanges{target:cir;opacity:1.0;color:'red'}
                    }
            ]

        }
    }
    Row{
        id:row;
        spacing:2;
        Box_s{}
        Box_s{}
        Box_s{}
        Box_s{}
        Box_s{}
        Box_s{}
        Box_s{}
        Box_s{}
        Box_s{}
        Box_s{}
        
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
        easing.type: Easing.InOutQuad;
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
        id:box1
        width: 20; height: 20;
        y: 60;
        opacity:0.5;
        color:'blue';
    }
    Item{
        id:box;
        y:100;
        Label {
            text:'生产者';
            y:20;
            x:-width;
        }
        Image{
            id:box_sour
            width:50;
            fillMode: Image.PreserveAspectFit;
            source:'file:/Users/mano233/Documents/c_projects/untitled3/arrow.svg'
        }
    }
    Connections {
        target: service;
        // 消费时触发
        function onFrontChanged(index){
            let item = row.children[index];
            let cir = item.children[0];
            cir.state = 'hidden';
            // let item = listView.itemAtIndex(index);
            // item.children[0].state = 'hidden';
            conAnima.to = item.x+25;
            conAnima.start();
        }
        // 生产时触发
        function onRealChanged(index){
             let item = row.children[index];
            let cir = item.children[0];
            cir.state = 'show';
            // let item = listView.itemAtIndex(index);
            // item.children[0].state = 'show';
            prodAnima.to = item.x-25;
            prodAnima.start();
        }
    }

}