import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.matterfish 1.0;

Page {
    id: settingsPage

    allowedOrientations: Orientation.All

    SilicaFlickable {
        id: listView
        anchors.fill: parent

        Column {
            width: parent.width
            height: pageHeader.height
            PageHeader {
                id: pageHeader
                title: qsTr("Settings")
            }

            SectionHeader {
                text: qsTr("Connection")
            }

            TextSwitch {
                checked: MatterfishSettings.onlineInBackground
                onCheckedChanged: {
                    MattermostClient.onlineInBackground = checked;
                    MatterfishSettings.onlineInBackground = checked;
                }
                text: qsTr("Keep online in background")
                description: qsTr("If enabled, the connection to the mattermost server will be kept alive and reconnected automatically on connection loss even if the app is in the background. This may increase the battery consumption.")
            }
        }
    }
}
