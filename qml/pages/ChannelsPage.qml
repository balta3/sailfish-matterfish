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

        section {
            property: "type"
            delegate: SectionHeader {
                text: switch(section) {
                      case "D": return qsTr("Direct messages");
                      case "G": return qsTr("Group messages");
                      case "O": return qsTr("Public channels");
                      case "P": return qsTr("Private channels");
                      default: return qsTr("Unknown");
                      }
            }
        }

        model: MattermostClient.selectedTeam.channels
        delegate: ListItem {
            Label {
                id: channelLabel
                text: model.displayName
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingMedium
                color: model.unread ? Theme.highlightColor : Theme.primaryColor
                //visible: model.type !== "D"
            }

            onClicked: {
                pageStack.push(Qt.resolvedUrl("PostsPage.qml"), {
                                    "selectedChannel": model.modelData
                               });
            }
        }
    }
}
