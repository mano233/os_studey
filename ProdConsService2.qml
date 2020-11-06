// import QtQuick 2.15
// import QtQuick.Controls 1.0
// import QtQuick.Window 2.15
// import com.mano.ProdConsService2 1.0
import QtQuick
import QtQuick.Controls 
import QtQuick.Window
import com.mano.ProdConsService2

Window {
    visible:true;
    ProdConsService2 {
        id: service;
    }
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
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
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
        Item{
            id:box1;
            anchors.bottom:parent.top;
            anchors.bottomMargin:35;
            x:20;
            Text{
                x:width+12;
                y:-6;
                text:'消费者';
            }
            Image{
                rotation:180;
                width:50;
                fillMode: Image.PreserveAspectFit;
                source:'file:/Users/mano233/Documents/c_projects/untitled3/arrow.svg'
            }
        }
        Item{
            id:box;
            x:-20;
            anchors.top:parent.bottom;
            Text{
                x:-width;
                y:20;
                text:'生产者';
            }
            Image{
                width:50;
                fillMode: Image.PreserveAspectFit;
                source:'file:/Users/mano233/Documents/c_projects/untitled3/arrow.svg'
            }
        }

    }
    Button {
        id:btn
        text:"start"
        onClicked: {
                service.start();
        }
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
    // 这种方式链接没有问题
    Component.onCompleted:{
        service.onFrontChanged.connect(onFrontChanged);
        service.onRealChanged.connect(onRealChanged);
    }
    // 使用这种方式链接，view.load()的时候会报错 EXC_BAD_ACCESS
    // Connections {
    //     target: service;
    //     // 消费时触发
    //     function onFrontChanged(index){
    //         let item = row.children[index];
    //         let cir = item.children[0];
    //         cir.state = 'hidden';
    //         // let item = listView.itemAtIndex(index);
    //         // item.children[0].state = 'hidden';
    //         conAnima.to = item.x+25;
    //         conAnima.start();
    //     }
    //     // 生产时触发
    //     function onRealChanged(index){
    //          let item = row.children[index];
    //         let cir = item.children[0];
    //         cir.state = 'show';
    //         // let item = listView.itemAtIndex(index);
    //         // item.children[0].state = 'show';
    //         prodAnima.to = item.x-25;
    //         prodAnima.start();
    //     }
    // }

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