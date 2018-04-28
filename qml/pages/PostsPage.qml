import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.matterfish 1.0;

Page {
    id: postsPage

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
                title: MattermostClient.selectedChannel.displayName
            }
        }

        model: MattermostClient.selectedChannel.posts
        delegate: ListItem {
            height: userLabel.height + Theme.paddingMedium + messageLabel.height < Theme.paddingMedium + userLabel.height + 2 + avatar.height ?
                        Theme.paddingMedium + userLabel.height + 2 + avatar.height
                      : userLabel.height + Theme.paddingMedium + messageLabel.height

            Label {
                id: userLabel
                text: model.user.username
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingMedium
                anchors.top: parent.top
                anchors.topMargin: Theme.paddingMedium
                color: Theme.secondaryColor
                font.pixelSize: Theme.fontSizeTiny
            }

            Label {
                id: dateLabel
                text: model.created.toLocaleString()
                anchors.right: parent.right
                anchors.rightMargin: Theme.paddingMedium
                anchors.top: parent.top
                anchors.topMargin: Theme.paddingMedium
                color: Theme.secondaryColor
                font.pixelSize: Theme.fontSizeTiny
            }

            Image {
                id: avatar
                source: "image://avatar/" + model.user.id
                anchors.top: parent.top
                anchors.topMargin: Theme.paddingMedium + userLabel.height + 2
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingMedium
            }

            Label {
                id: messageLabel
                text: model.message
                anchors.left: parent.left
                anchors.leftMargin: 2 * Theme.paddingMedium + avatar.width
                anchors.right: parent.right
                anchors.rightMargin: Theme.paddingMedium
                anchors.top: parent.top
                anchors.topMargin: dateLabel.height + Theme.paddingSmall
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeSmall
            }
        }
    }
}
