import QtQuick
import QtQuick.Controls
import QtQuick.Window
import com.mano233.DynamicAlloc

Window {
    function updateModel() {
		model.clear()
        let list = alloctor.get_list();
        for (let i = 0; i < list.length; i++) {
            let _size = list[i].size;
            let _alloc = list[i].alloc;
            model.append({
                "_alloc": _alloc,
                "_size": _size,
            });
		}
    }

    visible: true
    height: 400
    width: 400
	Component.onCompleted: {
		updateModel()
    }

    DynamicAlloc {
        id: alloctor
    }
	
    ListModel {
        id: model
    }

    Row {
        Column {
            Row {
                SpinBox {
                    // focusPolicy:Qt.ClickFocus

                    id: inp_size

                    editable: true
                    value: 0
                    to: 256
                    from: 8
                }

                Button {
                    text: 'enter'
                    onClicked: {
						inp_size.focus = false
						alloctor.malloc(inp_size.value)
						updateModel()
                    }
                }

            }

            ButtonGroup {
                id: radioGroup
            }

            Column {
                RadioButton {
                    text: '首次适应算法'
                    checked: true
                    ButtonGroup.group: radioGroup
                }

                RadioButton {
                    text: '循环首次适应算法'
                    ButtonGroup.group: radioGroup
                }

                RadioButton {
                    text: '最佳适应算法'
                    ButtonGroup.group: radioGroup
                }

                RadioButton {
                    text: '最坏适应算法'
                    ButtonGroup.group: radioGroup
                }

            }

        }

        ListView {
            model: model
			width: 100
			height:400
            clip:true
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
                    text: 'size:' + _size
                }

            }

        }

    }

}
