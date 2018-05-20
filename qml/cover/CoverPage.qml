import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.matterfish 1.0;

CoverBackground {
    Label {
        id: nameLabel
        text: "Matterfish"
        anchors.left: parent.left
        anchors.leftMargin: Theme.paddingMedium
        anchors.top: parent.top
        anchors.topMargin: Theme.paddingMedium
    }
    Label {
        text: MattermostClient.state
        anchors.left: parent.left
        anchors.leftMargin: Theme.paddingMedium
        anchors.top: nameLabel.bottom
        anchors.topMargin: Theme.paddingMedium
    }

    Image {
        id: messageCountIcon
        source: "image://theme/icon-m-message"
        anchors.right: parent.right
        anchors.rightMargin: Theme.paddingMedium
        anchors.bottom: mentionCountIcon.top
        anchors.bottomMargin: Theme.paddingMedium
    }
    Label {
        id: messageCountLabel
        text: MattermostClient.messageCount
        anchors.right: messageCountIcon.left
        anchors.rightMargin: Theme.paddingMedium
        anchors.bottom: messageCountIcon.bottom
        font.pixelSize: Theme.fontSizeExtraLarge
    }
    Label {
        id: mentionCountIcon
        text: "@"
        anchors.right: parent.right
        anchors.rightMargin: Theme.paddingMedium
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Theme.paddingMedium
        font.pixelSize: Theme.fontSizeExtraLarge
    }
    Label {
        id: mentionCountLabel
        text: MattermostClient.mentionCount
        anchors.right: mentionCountIcon.left
        anchors.rightMargin: Theme.paddingMedium
        anchors.bottom: mentionCountIcon.bottom
        font.pixelSize: Theme.fontSizeExtraLarge
    }
}
