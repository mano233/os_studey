import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts
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
                "_id": _id?_id:""
            });
        }
    }

    visible: true
    height: 400
    width: 400
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
			Layout.alignment:Qt.AlignTop
            RowLayout {
                Label {
                    text: "size:"
                }

                SpinBox {
                    id: inp_size
                    editable: true
                    value: 0
                    to: 256000
                    from: 8
				}
				Label{
					text:inp_size.value<=8?2*8:8*(parseInt((inp_size.value+15)/8))
				}

				Label {
                    text: "id:"
                }

                TextField {
                    id: inp_id

                    placeholderText: qsTr("Enter id")
                }

                Button {
                    text: 'malloc'
                    onClicked: {
						inp_size.focus = false
						inp_id.focus = false
                        alloctor.malloc(inp_id.text, inp_size.value)
                        inp_id.text = ""
                        updateModel()
                    }
				}

                Button {
                    text: 'free'
                    onClicked: {
                        inp_size.focus = false
                        alloctor.free(inp_id.text)
                        inp_id.text = ""
                        updateModel()
                    }
                }

            }

            ButtonGroup {
				id: radioGroup
				onClicked:{
					alloctor.setFitFun(button.value)
				}
            }

            Column {
				RadioButton {
					property int value:0
                    text: '首次适应算法'
                    checked: true
                    ButtonGroup.group: radioGroup
                }

                RadioButton {
                    text: '循环首次适应算法'
					property int value:1
                    ButtonGroup.group: radioGroup
                }

                RadioButton {
                    text: '最佳适应算法'
					property int value:2
                    ButtonGroup.group: radioGroup
                }

                RadioButton {
					property int value:3
                    text: '最坏适应算法'
                    ButtonGroup.group: radioGroup
                }

            }

        }

        ListView {
            model: model
            width: 100
            height: 400
            clip: true
            flickableDirection: Flickable.AutoFlickDirection
            spacing: 2
            delegate: Rectangle {
                width: 100
                height: _size
                border.color: "black"
                border.width: 1
                color: _alloc ? 'red' : 'green'

                Text {
                    visible: parent.height >= 12
                    anchors.centerIn: parent
                    text: _id?("id:"+_id+"size:"+_size):("size"+_size)
                }

            }

        }

    }

}
