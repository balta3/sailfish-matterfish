import QtQuick 2.0

import Sailfish.Silica 1.0

import harbour.matterfish 1.0;

Page {
    id: imagePage

    allowedOrientations: Orientation.All

    PageHeader {
        id: pageHeader
        title: MattermostClient.selectedFile.name
    }

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "image://file/" + MattermostClient.selectedFile.id
    }
}
