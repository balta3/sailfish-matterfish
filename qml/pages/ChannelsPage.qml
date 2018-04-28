import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.matterfish 1.0;

Page {
    id: channelsPage

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    onVisibleChanged: {
        console.log(MattermostClient.selectedTeam.channels);
    }

    PageHeader {
        id: pageHeader
        title: MattermostClient.selectedTeam.displayName + "(" + MattermostClient.selectedTeam.messageCount + ")"
    }

    SilicaListView {
        id: listView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: pageHeader.bottom

        clip: true

        model: MattermostClient.selectedTeam.channels
        delegate: ListItem {
            Label {
                id: channelLabel
                text: model.type + " - " + model.displayName
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingMedium
                color: model.unread ? Theme.highlightColor : Theme.primaryColor
                //visible: model.type !== "D"
            }

            onClicked: {
                console.log(model.modelData)
                MattermostClient.selectedChannel = model.modelData
                pageStack.push(Qt.resolvedUrl("PostsPage.qml"))
            }
        }
    }
}
