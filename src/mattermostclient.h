#ifndef MATTERMOSTCLIENT_H
#define MATTERMOSTCLIENT_H

#include <QObject>
#include <QVariantMap>
#include <QList>
#include <QMap>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QWebSocket>
#include <QQmlListProperty>

#include "mattermostteam.h"
#include "mattermostuser.h"
#include "mattermostpost.h"

class MattermostClient : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString host READ getHost WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(MattermostTeam* selectedTeam READ getSelectedTeam WRITE setSelectedTeam NOTIFY selectedTeamChanged)
    Q_PROPERTY(MattermostChannel* selectedChannel READ getSelectedChannel WRITE setSelectedChannel NOTIFY selectedChannelChanged)
    Q_PROPERTY(QQmlListProperty<MattermostTeam> teams READ getTeamsQML NOTIFY teamsChanged)
    Q_PROPERTY(QUrl baseURL READ getBaseURL WRITE setBaseURL NOTIFY baseURLChanged)
public:
    explicit MattermostClient(QObject *parent = nullptr);

    QString getHost() const;
    void setHost(const QString &value);

    QString getUsername() const;
    void setUsername(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    MattermostTeam *getSelectedTeam() const;
    void setSelectedTeam(MattermostTeam *value);

    QQmlListProperty<MattermostTeam> getTeamsQML();

    MattermostChannel *getSelectedChannel() const;
    void setSelectedChannel(MattermostChannel *value);

    QUrl getBaseURL() const;
    void setBaseURL(const QUrl &value);

    QString getAuthorization();

signals:
    void hostChanged(const QString& host);
    void usernameChanged(const QString& username);
    void passwordChanged(const QString& password);
    void selectedTeamChanged(const MattermostTeam* team);
    void selectedChannelChanged(const MattermostChannel* channel);
    void teamsChanged();
    void baseURLChanged(const QUrl& value);
public slots:
    void connectToHost();
    void refreshTeams();
    void refreshTeamUnreads();
    void refreshChannels(MattermostTeam* team);
    void refreshTeamMembers(MattermostTeam* team);
    void refreshUsers();
    void refreshChannelPosts(MattermostChannel* channel);
    void onResponse(QNetworkReply* reply);
    void onWebSocketConnected();
    void onWebSocketMessage(QString message);
    void onWebSocketError(QAbstractSocket::SocketError error);

private:
    QString host;
    QString username;
    QString password;
    QVariantMap user;
    QList<MattermostTeam*> teams;
    QMap<QString, MattermostUser*> users;

    MattermostTeam* selectedTeam;
    MattermostChannel* selectedChannel;

    QUrl baseURL;
    QNetworkAccessManager* netAccessManager;
    QWebSocket* webSocket;
    quint64 webSocketSeq;
    QString token;
};

#endif // MATTERMOSTCLIENT_H
