import QtQuick 2.2
import Sailfish.Silica 1.0

Dialog {
    id:dlg
    property alias valeur : n.text
    property alias titre: t.text
    property alias label: n.label
    property string dif: ""
    property int mini :1

    Column {
        width: parent.width

        DialogHeader { }

        SectionHeader { id:t }

        TextField {
            id: n
            width: parent.width
            focus:true

            EnterKey.enabled: text.length >= dlg.mini
            EnterKey.onClicked: dlg.accept()
        }
    }

    canAccept: (n.text.length >= dlg.mini) && (n.text !== dif)
}
