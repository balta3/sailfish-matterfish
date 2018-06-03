import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.matterfish 1.0;

Page {
    id: teamsPage

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: Column {
            width: parent.width
            height: pageHeader.height
            PageHeader {
                id: pageHeader
                title: "Teams"
            }
        }

        //height: parent.height - pageHeader.height
        //anchors.topMargin: pageHeader.height
        model: MattermostClient.teams
        delegate: ListItem {
            height: icon.height + Theme.paddingMedium
            contentHeight: height

            Image {
                id: icon
                source: "image://team/" + model.id
                anchors.top: parent.top
                anchors.topMargin: Theme.paddingMedium
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingMedium
                height: 128
                width: 128
            }
            Label {
                id: teamLabel
                text: model.displayName
                anchors.left: icon.right
                anchors.leftMargin: Theme.paddingMedium
                anchors.top: parent.top
                anchors.topMargin: Theme.paddingMedium
            }
            Image {
                id: messageCountIcon
                source: "image://theme/icon-s-message"
                anchors.right: parent.right
                anchors.rightMargin: Theme.paddingMedium
                anchors.top: parent.top
                anchors.topMargin: Theme.paddingMedium
                visible: model.messageCount > 0
            }
            Label {
                id: messageCountLabel
                text: model.messageCount
                anchors.right: messageCountIcon.left
                anchors.rightMargin: Theme.paddingMedium
                anchors.bottom: messageCountIcon.bottom
                visible: model.messageCount > 0
            }
            Label {
                id: mentionCountIcon
                text: "@"
                anchors.right: parent.right
                anchors.rightMargin: Theme.paddingMedium
                anchors.top: messageCountIcon.bottom
                anchors.topMargin: Theme.paddingMedium
                visible: model.mentionCount > 0
            }
            Label {
                id: mentionCountLabel
                text: model.mentionCount
                anchors.right: mentionCountIcon.left
                anchors.rightMargin: Theme.paddingMedium
                anchors.bottom: mentionCountIcon.bottom
                visible: model.mentionCount > 0
            }

            onClicked: {
                console.log(model.modelData)
                MattermostClient.selectedTeam = model.modelData
                pageStack.push(Qt.resolvedUrl("ChannelsPage.qml"))
            }
        }

        PullDownMenu {
            MenuItem {
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"));
            }
            MenuItem {
                text: qsTr("Connect")
                visible: MattermostClient.state == 'offline'
                onClicked: MattermostClient.connectToHost();
            }
            MenuItem {
                text: qsTr("Disconnect")
                visible: MattermostClient.state == 'online'
                onClicked: MattermostClient.disconnectFromHost();
            }
            MenuLabel {
                id: stateLabel
                text: MattermostClient.state
            }
        }
    }
}
