#include "mattermostavatarimageprovider.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

MattermostAsyncImageResponse::MattermostAsyncImageResponse(QString userid, QUrl baseURL, QString authorization) {
    qDebug() << "loading avatar for user" << userid;
    this->netAccessManager = new QNetworkAccessManager(this);
    QObject::connect(this->netAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResponse(QNetworkReply*)));

    QUrl avatarURL = baseURL;
    avatarURL.setPath("/api/v4/users/" + userid + "/image");

    QNetworkRequest request;
    request.setUrl(avatarURL);
    request.setRawHeader(QString("Authorization").toUtf8(), authorization.toUtf8());

    this->netAccessManager->get(request);
}

QQuickTextureFactory* MattermostAsyncImageResponse::textureFactory() const {
    return QQuickTextureFactory::textureFactoryForImage(this->image);
}

void MattermostAsyncImageResponse::onResponse(QNetworkReply *reply) {
    qDebug() << "response";
    QNetworkReply::NetworkError error = reply->error();
    if (error == QNetworkReply::NoError) {
        this->image.loadFromData(reply->readAll());
    }
    emit this->finished();
}

MattermostAvatarImageProvider::MattermostAvatarImageProvider(MattermostClient* mattermostClient) : QQuickAsyncImageProvider()
{
    this->client = mattermostClient;
}

QQuickImageResponse *MattermostAvatarImageProvider::requestImageResponse(const QString &id, const QSize &requestedSize)
{
    MattermostAsyncImageResponse* resp = new MattermostAsyncImageResponse(id, this->client->getBaseURL(), this->client->getAuthorization());
    return resp;
}
