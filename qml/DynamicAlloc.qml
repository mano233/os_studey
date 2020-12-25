import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import com.mano233.DynamicAlloc

Window {
    function updateModel() {
        model.clear();
        let list = alloctor.get_list();
        for (let i = 0; i < list.length; i++) {
            let _size = list[i].size;
            let _alloc = list[i].alloc;
            let _id = list[i].id;
            model.append({
                "_alloc": _alloc,
                "_size": _size,
                "_addr": list[i].addr ? list[i].addr : "",
                "_id": _id ? _id : ""
            });
        }
    }

    visible: true
    height: 400
    width: 800
    Component.onCompleted: {
        updateModel();
    }

    DynamicAlloc {
        id: alloctor
    }

    ListModel {
        id: model
    }

    RowLayout {
        ColumnLayout {
            Layout.alignment: Qt.AlignTop

            ColumnLayout {
                RowLayout {
                    Label {
                        text: "分配的大小(byte):"
                    }

                    SpinBox {
                        id: inp_size

                        editable: true
                        value: 0
                        to: 256000
                        from: 8
                    }

                    Label {
                        text: "双字对齐" + (inp_size.value <= 8 ? 2 * 8 : 8 * (parseInt((inp_size.value + 15) / 8))) + "(byte)"
                    }

                }

                ButtonGroup {
                    id: radioGroup

                    onClicked: {
                        alloctor.setFitFun(button.value);
                    }
                }

                Column {
                    RadioButton {
                        property int value: 0

                        text: '首次适应算法'
                        checked: true
                        ButtonGroup.group: radioGroup
                    }

                    RadioButton {
                        property int value: 1

                        text: '循环首次适应算法'
                        ButtonGroup.group: radioGroup
                    }

                    RadioButton {
                        property int value: 2

                        text: '最佳适应算法'
                        ButtonGroup.group: radioGroup
                    }

                    RadioButton {
                        property int value: 3

                        text: '最坏适应算法'
                        ButtonGroup.group: radioGroup
                    }

                }

                RowLayout {
                    Label {
                        text: "内存块名:"
                    }

                    TextField {
                        id: inp_id

                        placeholderText: qsTr("Enter id")
                    }

                }

                RowLayout {
                    Button {
                        text: 'malloc'
                        onClicked: {
                            inp_size.focus = false;
                            inp_id.focus = false;
                            alloctor.malloc(inp_id.text, inp_size.value);
                            inp_id.text = "";
                            updateModel();
                            mem_list.positionViewAtBeginning();
                        }
                    }

                    Button {
                        text: 'free'
                        onClicked: {
                            inp_size.focus = false;
                            alloctor.free(inp_id.text);
                            inp_id.text = "";
                            updateModel();
                            mem_list.positionViewAtBeginning();
                        }
                    }

                }

            }

        }

        ListView {
            id: mem_list

            model: model
            height: 400
            width: 200
            flickableDirection: Flickable.AutoFlickDirection
            spacing: 3

            delegate: Rectangle {
                width: 200
                height: _size
                color: _alloc ? '#FF958E' : '#C2E095'

                Label {
                    text: _addr ? '0x' + _addr : ''
                    x: 200 + 10
                }

                Text {
                    visible: parent.height >= 12
                    font.family: "Arial"
                    font.pixelSize: 12
                    font.weight: Font.Bold
                    color: "white"
                    anchors.centerIn: parent
                    text: _id ? ("id:" + _id + "    size:" + _size + "byte") : ("size" + _size)
                }

            }

        }

    }

}
