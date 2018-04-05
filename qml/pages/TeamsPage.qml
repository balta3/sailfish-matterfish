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
            //width: parent.width
            //height: Theme.itemSizeSmall
            //height: childrenRect.height + Theme.paddingMedium
            Label {
                id: teamLabel
                text: model.displayName
                anchors.leftMargin: Theme.paddingMedium
            }
            onClicked: {
                console.log(model.modelData)
                MattermostClient.selectedTeam = model.modelData
                pageStack.push(Qt.resolvedUrl("ChannelsPage.qml"))
            }
        }
    }
}
