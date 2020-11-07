import QtQuick 2.0
Rectangle {
    id: window;
    width: 800;
    height: 480;
    function updatePos (item_orig, item_dest) {
        var pos_abs = window.mapFromItem (item_orig.parent, item_orig.x, item_orig.y);
        return window.mapToItem (item_dest.parent, pos_abs.x, pos_abs.y);
    }
    Rectangle {
        id: rectGreen;
        x: 100;
        y: 100;
        width: 50;
        height: 50;
        color: "green";
        NumberAnimation on x {
                    id:anima1
                    from: 0
                    running:true
                    to: 360
        }
    }
    Rectangle {
        id: rectBlue;
        x: pos.x + 50;
        y: pos.y + 50;
        width: 50;
        height: 50;
        color: "blue";

        property var pos : updatePos (rectGreen, rectBlue);
    }
}