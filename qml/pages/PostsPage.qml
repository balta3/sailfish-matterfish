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

        footer: Item {
            height: newMessageTextField.height
            width: parent.width

            TextArea {
                id: newMessageTextField
                anchors.left: parent.left
                anchors.right: sendButton.left
                anchors.bottom: parent.bottom
                text: MattermostClient.newMessage
            }
            IconButton {
                id: sendButton
                anchors.right: parent.right
                anchors.top: parent.top
                icon.source: "image://theme/icon-m-message?" + (newMessageTextField.text.length > 0
                                                             ? Theme.primaryColor
                                                             : Theme.highlightColor)
                onClicked: {
                    MattermostClient.newMessage = newMessageTextField.text;
                    MattermostClient.sendNewMessage();
                }
            }
        }

        section {
            property: "createdDay"
            delegate: SectionHeader {
                text: section
            }
        }

        model: MattermostClient.selectedChannel.posts
        delegate: ListItem {
            id: postItem
            height: userLabel.height + Theme.paddingMedium + messageLabel.height + attachementsContainer.height < Theme.paddingMedium + avatar.height ?
                        Theme.paddingMedium + avatar.height
                      : userLabel.height + Theme.paddingMedium + messageLabel.height + attachementsContainer.height
            contentHeight: height

            property var files: model.files

            Label {
                id: userLabel
                text: model.user.username
                anchors.left: avatar.right
                anchors.leftMargin: Theme.paddingMedium
                anchors.top: parent.top
                anchors.topMargin: Theme.paddingMedium
                color: Theme.secondaryColor
                font.pixelSize: Theme.fontSizeTiny
            }

            Label {
                id: timeLabel
                text: model.created.toLocaleTimeString(Qt.locale(), Locale.ShortFormat)
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
                anchors.topMargin: Theme.paddingMedium
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingMedium
                height: 128
                width: 128
            }

            Label {
                id: messageLabel
                text: model.message
                anchors.left: parent.left
                anchors.leftMargin: 2 * Theme.paddingMedium + avatar.width
                anchors.right: parent.right
                anchors.rightMargin: Theme.paddingMedium
                anchors.top: parent.top
                anchors.topMargin: timeLabel.height + Theme.paddingSmall
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeSmall
            }

            Item {
                id: attachementsContainer
                anchors.left: messageLabel.left
                anchors.top: messageLabel.bottom
                height: attachementsList.height + Theme.paddingMedium
                width: parent.width

                ListView {
                    id: attachementsList
                    model: postItem.files
                    height: contentHeight
                    width: parent.width
                    anchors.top: parent.top
                    anchors.topMargin: Theme.paddingMedium
                    delegate: ListItem {
                        height: thumbnail.visible ? fileIcon.height + thumbnail.height + Theme.paddingSmall : fileIcon.height
                        width: parent.width
                        contentHeight: height
                        Component.onCompleted: if (model.name.length === 0) MattermostClient.initFile(model.id);

                        Image {
                            id: fileIcon
                            height: Theme.iconSizeSmall
                            fillMode: Image.PreserveAspectFit
                            source: model.mimeType.match("^image/") ? "image://theme/icon-m-image" : "image://theme/icon-s-attach"
                        }
                        Label {
                            anchors.left: fileIcon.right
                            anchors.leftMargin: Theme.paddingSmall
                            anchors.bottom: fileIcon.bottom
                            text: model.name.length === 0 ? model.id : model.name
                            font.pixelSize: Theme.fontSizeTiny
                        }
                        Image {
                            id: thumbnail
                            anchors.top: fileIcon.bottom
                            anchors.topMargin: Theme.paddingSmall
                            anchors.left: fileIcon.right
                            anchors.leftMargin: Theme.paddingSmall
                            width: parent.width
                            fillMode: Image.PreserveAspectFit
                            horizontalAlignment: Image.AlignLeft
                            source: "image://filethumbnail/" + model.id
                            visible: model.hasPreviewImage
                        }
                    }
                }
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
