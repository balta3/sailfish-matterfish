#ifndef MATTERMOSTAVATARIMAGEPROVIDER_H
#define MATTERMOSTAVATARIMAGEPROVIDER_H

#include <QQuickAsyncImageProvider>

#include "mattermostclient.h"

class MattermostAsyncImageResponse : public QQuickImageResponse {
    Q_OBJECT
public:
    MattermostAsyncImageResponse(QUrl url, QString authorization);

    QQuickTextureFactory *textureFactory() const;

public slots:
    void onResponse(QNetworkReply* reply);

private:
    QNetworkAccessManager* netAccessManager;
    QImage image;
};

class MattermostAvatarImageProvider : public QQuickAsyncImageProvider
{
public:
    MattermostAvatarImageProvider(MattermostClient* mattermostClient);
    QQuickImageResponse* requestImageResponse(const QString &id, const QSize &requestedSize);

private:
    MattermostClient* client;
};

class MattermostTeamIconImageProvider : public QQuickAsyncImageProvider
{
public:
    MattermostTeamIconImageProvider(MattermostClient* mattermostClient);
    QQuickImageResponse* requestImageResponse(const QString &id, const QSize &requestedSize);

private:
    MattermostClient* client;
};

class MattermostFileImageProvider : public QQuickAsyncImageProvider
{
public:
    MattermostFileImageProvider(MattermostClient* mattermostClient);
    QQuickImageResponse* requestImageResponse(const QString &id, const QSize &requestedSize);

private:
    MattermostClient* client;
};

class MattermostFileThumbnailImageProvider : public QQuickAsyncImageProvider
{
public:
    MattermostFileThumbnailImageProvider(MattermostClient* mattermostClient);
    QQuickImageResponse* requestImageResponse(const QString &id, const QSize &requestedSize);

private:
    MattermostClient* client;
};

#endif // MATTERMOSTAVATARIMAGEPROVIDER_H
