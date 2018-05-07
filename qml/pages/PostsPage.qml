import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.matterfish 1.0;

Page {
    id: postsPage

    allowedOrientations: Orientation.All

    PageHeader {
        id: pageHeader
        title: MattermostClient.selectedChannel.displayName

        PullDownMenu {
            MenuItem {
                text: qsTr("Reload")
            }
        }
    }

    SilicaListView {
        id: listView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: pageHeader.bottom

        property bool autoScrollToBottom: true

        clip: true
        verticalLayoutDirection: ListView.BottomToTop

        header: Item {
            height: newMessageTextField.height
            width: parent.width

            TextArea {
                id: newMessageTextField
                anchors.left: parent.left
                anchors.right: sendButton.left
                anchors.bottom: parent.bottom
            }
            IconButton {
                id: sendButton
                anchors.right: parent.right
                anchors.top: parent.top
                icon.source: "image://theme/icon-m-message?" + (newMessageTextField.text.length > 0
                                                             ? Theme.primaryColor
                                                             : Theme.highlightColor)
                onClicked: MattermostClient.sendNewMessage();
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

        PushUpMenu {
            MenuItem {
                text: qsTr("Reload")
                onClicked: MattermostClient.refreshChannelPosts(MattermostClient.selectedChannel)
            }
        }
    }
}
