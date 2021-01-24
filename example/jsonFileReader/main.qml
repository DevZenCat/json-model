import QtQuick 2.12
import QtQuick.Controls 2.5

import JsonListModel 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

    ScrollView {
        anchors.fill: parent

        ListView {
            width: parent.width
            model: jsonListModel
            delegate: ItemDelegate {
                text: "Item: name = " + model.name + ", description = " + model.description
                width: parent.width
            }
        }

        opacity: jsonListModel.status == 2 ? 1 : 0

        Behavior on opacity {
            NumberAnimation { duration: 100 }
        }
    }

    Image {
        id: loadingImage

        anchors.centerIn: parent

        height: 50
        width: 50

        source: "qrc:/../placeholder.png"

        opacity: {
            return jsonListModel.status != 2 ? 1.0 : 0.0
        }

        Behavior on opacity {
            NumberAnimation { duration: 100 }
        }

        RotationAnimator {
            target: loadingImage
            loops: Animation.Infinite
            from: 0
            to: 360
            duration: 1000
            running: loadingImage.opacity > 0
        }
    }

    Component.onCompleted:
    {
        console.debug("Component.onCompleted", jsonListModel.status, JsonListModel.Complete, jsonListModel.status == 0);
        jsonListModel.load(":/listData.json")
    }
}
