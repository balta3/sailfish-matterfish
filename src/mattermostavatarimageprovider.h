#ifndef MATTERMOSTAVATARIMAGEPROVIDER_H
#define MATTERMOSTAVATARIMAGEPROVIDER_H

#include <QQuickAsyncImageProvider>

#include "mattermostclient.h"

class MattermostAsyncImageResponse : public QQuickImageResponse {
    Q_OBJECT
public:
    MattermostAsyncImageResponse(QString userid, QUrl baseURL, QString authorization);

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

#endif // MATTERMOSTAVATARIMAGEPROVIDER_H
