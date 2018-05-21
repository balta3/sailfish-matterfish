#include "mattermostavatarimageprovider.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

MattermostAsyncImageResponse::MattermostAsyncImageResponse(QUrl url, QString authorization) {
    this->netAccessManager = new QNetworkAccessManager(this);
    QObject::connect(this->netAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResponse(QNetworkReply*)));

    QNetworkRequest request;
    request.setUrl(url);
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
    QUrl avatarURL = this->client->getBaseURL();
    avatarURL.setPath("/api/v4/users/" + id + "/image");
    MattermostAsyncImageResponse* resp = new MattermostAsyncImageResponse(avatarURL, this->client->getAuthorization());
    return resp;
}

MattermostTeamIconImageProvider::MattermostTeamIconImageProvider(MattermostClient *mattermostClient) : QQuickAsyncImageProvider()
{
    this->client = mattermostClient;
}

QQuickImageResponse *MattermostTeamIconImageProvider::requestImageResponse(const QString &id, const QSize &requestedSize)
{
    QUrl teamIconURL = this->client->getBaseURL();
    teamIconURL.setPath("/api/v4/teams/" + id + "/image");
    MattermostAsyncImageResponse* resp = new MattermostAsyncImageResponse(teamIconURL, this->client->getAuthorization());
    return resp;
}

MattermostFileImageProvider::MattermostFileImageProvider(MattermostClient *mattermostClient) : QQuickAsyncImageProvider()
{
    this->client = mattermostClient;
}

QQuickImageResponse *MattermostFileImageProvider::requestImageResponse(const QString &id, const QSize &requestedSize)
{
    QUrl fileThumbnailURL = this->client->getBaseURL();
    fileThumbnailURL.setPath("/api/v4/files/" + id);
    MattermostAsyncImageResponse* resp = new MattermostAsyncImageResponse(fileThumbnailURL, this->client->getAuthorization());
    return resp;
}

MattermostFileThumbnailImageProvider::MattermostFileThumbnailImageProvider(MattermostClient *mattermostClient) : QQuickAsyncImageProvider()
{
    this->client = mattermostClient;
}

QQuickImageResponse *MattermostFileThumbnailImageProvider::requestImageResponse(const QString &id, const QSize &requestedSize)
{
    QUrl fileThumbnailURL = this->client->getBaseURL();
    fileThumbnailURL.setPath("/api/v4/files/" + id + "/thumbnail");
    MattermostAsyncImageResponse* resp = new MattermostAsyncImageResponse(fileThumbnailURL, this->client->getAuthorization());
    return resp;
}
