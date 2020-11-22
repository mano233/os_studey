// import QtQuick 2.15
// import QtQuick.Controls 1.0
// import QtQuick.Window 2.15
// import com.mano.ProdConsService2
import QtQuick
import QtQuick.Controls 
import QtQuick.Window
import com.mano.ProdConsService2 1.0

Window {
    visible:true;
    width:720;
    height:640;

    component Box_s:Rectangle{
        width: 50;height: 50;
        color: "white"
        border.color: "black"
        border.width: 1;
        Rectangle{
            id:cir;
            x:10;
            y:-20;
            opacity:0;
            radius:width/2;
            color:'red';width:30;height:30;
            transitions:[
                    Transition {
                        from: "*"; to: "show";
                        NumberAnimation {
                            properties: "opacity,y";
                            easing.type: Easing.InOutQuad;
                            duration: 200;
                        }
                    },
                    Transition {
                        from: "show"; to: "hidden";
                        NumberAnimation {
                            properties: "opacity,y";
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
                    PropertyChanges{target:cir;opacity:0.0;color:'blue';y:-20;}
                },
                State {
                    name: "show";
                    PropertyChanges{target:cir;opacity:1.0;color:'red';y:10;}
                }
            ]

        }
    }
    Rectangle {
        id: rotatingBox
        width: 50
        height: 50
        color: "lightsteelblue"
        RotationAnimator {
            target: rotatingBox;
            from: 0;
            to: 360;
            duration: 1000
            loops: Animation.Infinite
            running: true
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
                id:con_text
                x:width+12;
                y:-6;
                text:'消费者';
            }
            Image{
                id:icon
                rotation:180;
                width:50;
                fillMode: Image.PreserveAspectFit;
                source:'qrc:/arrow.svg';
                ShaderEffect {
                    property variant src: icon
                    anchors.fill: parent
                    //width: 100; height: 100
                    //vertexShader: "file:/Users/mano233/Documents/c_projects/untitled3/qml/shader.vert.qsb"
                    fragmentShader: "qrc:/shader.frag.qsb"
                }
            }
        }
        Item{
            id:box;
            x:-20;
            anchors.top:parent.bottom;
            Text{
                id:pro_text
                x:-width;
                y:20;
                text:'生产者';
            }
            Image{
                width:50;
                fillMode: Image.PreserveAspectFit;
                source:'qrc:/arrow.svg'
            }
        }

    }
    Column{
        Button {
            text:"start"
            onClicked: {
                service.start();
            }
        }
        Switch {
            text: qsTr("锁定生产者")
            onToggled:{
                if(checked){
                    prodAnima.complete();
                    service.lock_producer();
                }else{
                    service.unlock_producer();
                }
            }
        }
        Switch {
            text: qsTr("锁定消费者")
            onToggled:{
                if(checked){
                    conAnima.complete();
                    
                    service.lock_consumer();
                }else{
                    service.unlock_consumer();
                }
            }
        }
    }
    
    PropertyAnimation {
        id: prodAnima;
        target: box;
        easing.type: Easing.InOutQuad;
        property: "x";
        duration: 500;
        onStarted:{
            service.lock_producer();
        }
        onFinished:{
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

    Text{
        text:"生产者消费者动画模拟"
        y:100
        anchors.horizontalCenter: parent.horizontalCenter
        
        font{
            family: "SF Pro Display"
            pointSize: 32
        }
    }
    ListModel {
        id:contactModel
    } 
    Component {
        id: contactDelegate
        Item {
            height:30
            Text { text: str }
        }
    }
    ListView {
        id: list
        x:300;
        width: 180; height: parent.height
        model: contactModel
        delegate: contactDelegate
    }

    onClosing:{
        service.quit();
    }

    ProdConsService2 {
        id: service
        onLog:{
            contactModel.append({str:str})
        }
        onReadyConsume:(index)=>{
            let item = row.children[index];
            conAnima.to = item.x+25;
            con_text.text = "消费者(正在消费...)";
            conAnima.start();
        }
        onConsumed:(index)=>{
            let item = row.children[index];
            let cir = item.children[0];
            con_text.text = "消费者(正在等待...)";
            cir.state = 'hidden';
        }
        onReadyProduce:(index)=>{
            let item = row.children[index];
            prodAnima.to = item.x-25;
            pro_text.text="生产者(正在生产...)"
            prodAnima.start();
        }
        onProduced:(index)=>{
            let item = row.children[index];
            let cir = item.children[0];
            pro_text.text="生产者(正在等待...)"
            cir.state = 'show';
           
        }
    }
}