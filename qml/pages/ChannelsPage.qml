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

    SilicaListView {
        id: listView
        anchors.fill: parent

        header: Column {
            width: parent.width
            height: pageHeader.height
            PageHeader {
                id: pageHeader
                title: MattermostClient.selectedTeam.displayName + "(" + MattermostClient.selectedTeam.channels.length + ")"
            }
        }

        //height: parent.height - pageHeader.height
        //anchors.topMargin: pageHeader.height
        model: MattermostClient.selectedTeam.channels
        delegate: ListItem {
            //width: parent.width
            //height: Theme.itemSizeSmall
            //height: childrenRect.height + Theme.paddingMedium
            Label {
                id: channelLabel
                text: model.type + " - " + model.displayName
                anchors.leftMargin: Theme.paddingMedium
                //visible: model.type !== "D"
            }
            //Label {
            //    id: dmLabel
            //    text: MattermostClient.selectedTeam.getMemberByDirectMessageChannelId(model.id).userId
            //    anchors.leftMargin: Theme.paddingMedium
            //    visible: model.type === "D"
            //}
        }
    }
}
