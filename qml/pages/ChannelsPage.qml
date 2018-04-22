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
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingMedium
                color: model.unread ? Theme.highlightColor : Theme.primaryColor
                //visible: model.type !== "D"
            }

            Label {
                id: dates
                text: model.member.lastViewed.toLocaleDateString(Qt.locale("de_DE")) + " - " + model.lastPostAt.toLocaleDateString(Qt.locale("de_DE"))
                //text: MattermostClient.selectedTeam.getMemberByDirectMessageChannelId(model.id).lastUpdated.toLocaleDateString(Qt.locale("de_DE")) + " - " + MattermostClient.selectedTeam.getMemberByDirectMessageChannelId(model.id).lastViewed.toLocaleDateString(Qt.locale("de_DE"))
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingMedium
                font.pixelSize: Theme.fontSizeExtraSmall
                visible: false
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
