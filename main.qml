import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import com.mycompany.messaging 1.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Material 2.4
//import io.qt.client 1.0

ApplicationWindow {
    property int default_pix_density: 5  //pixel density of my current screen
    property int scale_factor: Screen.pixelDensity/default_pix_density
    visible: true
    width: 800
    height: 640
    title: qsTr("Scoipe")
    //color: "#292b2f"
      
    Material.theme: Material.Dark
    Material.accent: Material.Purple

    Rectangle {
        id: chatWindow
        x: 30
        y: 30
        height: 515
        layer.enabled: true
        width: 500
        //color: "#5e5e5e"
        //border { width: 1; color: "black" }
        Material.elevation: 6
        Material.background: Material.color(Material.BlueGrey, Material.Shade900)
        Page {
            id: root
            layer.enabled: true
            anchors.fill: parent
            property string inConversationWith

            ColumnLayout {
                anchors.fill: parent
                layer.enabled: true

                ListView {
                    id: listView
                    layer.enabled: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    verticalLayoutDirection: ListView.BottomToTop
                    spacing: 12
                    model: client.messages
                    delegate: Column {
                        anchors.right: sentByMe ? parent.right : undefined
                        spacing: 6
                        layer.enabled: true
                        readonly property bool sentByMe: model.sender === "Me"

                        Row {
                            id: messageRow
                            spacing: 6
                            anchors.right: sentByMe ? parent.right : undefined
                            layer.enabled: true
                            Image {
                                id: avatar
                                source: !sentByMe ? "qrc:/Images/" + model.sender.replace(" ", "_") + ".png" : ""
                            }

                            Rectangle {
                                id: messa
                                width: Math.min(messageText.implicitWidth + 24, listView.width - /*avatar.width*/ - messageRow.spacing)
                                height: messageText.implicitHeight + 24
                                color: sentByMe ? "lightgrey" : "steelblue"
                                anchors.bottom: messageRow.bottom
                                border {width: 1; color: "black"}
                                radius: 10
                                layer.enabled: true
                                Label {
                                    id: messageText
                                    text: model.content
                                    color: sentByMe ? "black" : "white"
                                    anchors.fill: parent
                                    anchors.margins: 12
                                    wrapMode: Label.Wrap
                                } // End Label
                            } // End Rectangle
                        } // End Row

                        Label {
                            id: timestampText
                            text: Qt.formatDateTime(model.date, "d MMM hh:mm")
                            color: "lightgrey"
                            anchors.right: sentByMe ? parent.right : undefined
                            anchors.margins: 10
                        } // End Label
                    } // End Column

                    ScrollBar.vertical: ScrollBar {}
                } // End ListView
            } // End ColumnLayout
        } // End Page
    } // End Rectangle

    
    Rectangle {
        id: peopleInChat
        x: 550
        y: 30
        height: 515
        width: 230
        //color: "#5e5e5e"
        //border { width: 1; color: "black" }
        Material.elevation: 6
        Material.background: Material.color(Material.BlueGrey, Material.Shade900)
        Page {
            anchors.fill: parent
            header: Label {
                padding: 10
                text: qsTr("Contacts")
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            ListView {
                id: listView2
                anchors.fill: parent
                topMargin: 48
                leftMargin: 48
                bottomMargin: 48
                rightMargin: 48
                spacing: 20
                model: ["Albert Einstein", "Blaise Pascal", "Isaac Newton", "Narrator"]
                delegate: ItemDelegate {
                    text: modelData
                    leftPadding: avatar2.implicitWidth + 10
                    
                    Image {
                        id: avatar2
                        source: "qrc:/Images/" + modelData.replace(" ", "_") + ".png"
                    }
                }
            }
        }
    }

    Rectangle {
        id: textEditor
        x: 30
        y: 558
        width: 500
        height: messageText2.contentHeight+5
        Layout.maximumHeight: 60
        Material.elevation: 6
        Material.background: Material.color(Material.BlueGrey, Material.Shade900)
        color: "#263238"
        //radius: 8 // This gives rounded corners to the Rectangle
        //border { width: 1; color: "black" } // This sets a 3px wide black border to be drawn
        ScrollView {
            id: view
            anchors.fill: parent
            TextInput {
                id: messageText2
                width: 490
                height: 73
                layer.enabled: true
                autoScroll: true
                selectByMouse: true
                color: "white"
                font.family: "Helvetica"
                verticalAlignment: Text.AlignLeft
                font.pointSize: 10
                focus: true
                wrapMode: TextArea.Wrap
                readOnly: false
                onAccepted: {
                    client.sendMessage(messageText2.text)
                    clear()
                    messageText2.focus = true
                } // End onAccepted
            } // End TextInput
        } // End ScrollView
        states: [
            State {
                name: wrap
                when: textEditor.height > 90
                    PropertyChanges {
                        target: textEditor
                        height: 75
                    } // End PropertyChanges
            } // End State
        ] // End states
    } // End Rectangle

    Dialog {
        id: newConnDialog
        title: "Connect to server"
        height: 150
        width: 300
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        
        Material.theme: Material.Dark
        Material.accent: Material.Purple
        
        onAccepted: {
            client.connectToServer(newFolderName.text, newFolderIp.text)
            newConnDialog.close()
            messageText2.focus = true
        }
        Column {
            anchors.fill: parent
            Text {
                text: "Username"
                height: 40
            }
            TextField {
                id: newFolderName
                width: parent.width * 0.75
                focus: true
                onFocusChanged: console.log("Focus changed " + focus)
            }
            Text {
                text: "Ip"
                height: 40
            }
            TextField {
                id: newFolderIp
                width: parent.width * 0.75
                focus: true
                onFocusChanged: console.log("Focus changed " + focus)
            }
        }
    }

    Button {
        x: 550
        y: 550
        width: 230
        
        text: "Connect to server"
        onClicked: newConnDialog.open()
    }
} // End Window
