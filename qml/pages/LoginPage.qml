import QtQuick 2.0
import Sailfish.Silica 1.0

import harbour.matterfish 1.0;

Dialog {
    id: login
    allowedOrientations: Orientation.Portrait;

    acceptDestination: Qt.resolvedUrl("TeamsPage.qml").toString()
    canAccept: true

    onDone: {
        MattermostClient.host = host.text;
        MattermostClient.username = username.text;
        MattermostClient.password = password.text;
        MattermostClient.connectToHost();
    }

    DialogHeader {
        id: header
        acceptText: "Verbinden"
    }

    Column {
        anchors.top: header.bottom
        width: parent.width
        Label {
            text: "Host"
        }
        TextField {
            id: host
            width: parent.width
            text: MattermostClient.host
        }
        Label {
            text: "Benutzername"
        }
        TextField {
            id: username
            width: parent.width
            text: MattermostClient.username
        }
        Label {
            text: "Passwort"
        }
        TextField {
            id: password
            width: parent.width
            text: MattermostClient.password
        }
    }
}
