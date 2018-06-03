import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.matterfish 1.0;

Dialog {
    id: login
    allowedOrientations: Orientation.Portrait;

    acceptDestination: Qt.resolvedUrl("TeamsPage.qml").toString()
    canAccept: true

    onDone: {
        MatterfishSettings.host = host.text;
        MattermostClient.host = host.text;
        MatterfishSettings.username = username.text;
        MattermostClient.username = username.text;
        MatterfishSettings.password = password.text;
        MattermostClient.password = password.text;
        MattermostClient.onlineInBackground = MatterfishSettings.onlineInBackground;
        MattermostClient.connectToHost();
    }

    DialogHeader {
        id: header
        acceptText: "Verbinden"
    }

    Column {
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.leftMargin: Theme.paddingMedium
        anchors.right: parent.right
        anchors.rightMargin: Theme.paddingMedium
        width: parent.width
        Label {
            text: qsTr("Host")
        }
        TextField {
            id: host
            width: parent.width
            text: MatterfishSettings.host
        }
        Label {
            text: qsTr("Username")
        }
        TextField {
            id: username
            width: parent.width
            text: MatterfishSettings.username
        }
        Label {
            text: qsTr("Password")
        }
        PasswordField {
            id: password
            width: parent.width
            text: MatterfishSettings.password
        }
    }
}
