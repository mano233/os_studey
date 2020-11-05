import QtQuick 2.15
import QtQuick.Controls 1.1
import com.mano.ProdConsService2 1.0

Rectangle {
    property double lastConX;
    property double lastProdX;
    Component {
        id: contactDelegate
        Rectangle {
            width: 50
            height: 50
            color: "white"
            border.color: "black"
            border.width: 1;
            Rectangle{
                anchors.verticalCenter:parent.verticalCenter;
                anchors.horizontalCenter:parent.horizontalCenter;
                visible:vis;
                color:'red';
                opacity:1;
                width:30;
                height:30;
            }
        }
        
    }

    ListModel {
        id: contactModel
        ListElement {
            index:0;
            vis:false;
        }
        ListElement {
            index:1;
            vis:false;
        }
        ListElement {
            index:2
            vis:false;
        }
        ListElement {
            index:3;
            vis:false;
        }
        ListElement {
            index:4;
            vis:false;
        }
        ListElement {
            index:5;
            vis:false;
        }
        ListElement {
            index:6;
            vis:false;
        }
        ListElement {
            index:7;
            vis:false;
        }
        ListElement {
            index:8;
            vis:false;
        }
        ListElement {
            index:9;
            vis:false;
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
        from:lastProdX;
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
        from:lastConX;
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
            lastConX = box1.x;
            contactModel.set(index,{vis:false});
            conAnima.to =listView.itemAtIndex(index).x;
            conAnima.start();
        }
        // 生产时触发
        function onRealChanged(index){
            lastProdX = box.x;
            contactModel.set(index,{vis:true});
            prodAnima.to = listView.itemAtIndex(index).x;
            prodAnima.start();
        }
    }

}