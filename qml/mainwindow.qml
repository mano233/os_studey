//import QtQuick 2.0
//import QtQuick.Window 2.15
//import QtQuick.Controls 2.15

import QtQuick
import QtQuick.Window
import QtQuick.Controls

ApplicationWindow{
    visible: true
    width: 800
    id: window
    height: 480

    menuBar: MenuBar {
            Menu {
                title: "文件"
                MenuItem { text: "Open..." }
                MenuItem { text: "Close" }
            }
            Menu {
                title: "进程管理"
                MenuItem { text: "进程状态转换" }
                MenuItem { text: "生产者消费者" }
                MenuItem { text: "Paste" }
            }
        }
}