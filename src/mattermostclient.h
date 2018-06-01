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
    Q_PROPERTY(QString newMessage READ getNewMessage WRITE setNewMessage NOTIFY newMessageChanged)
    Q_PROPERTY(QQmlListProperty<MattermostTeam> teams READ getTeamsQML NOTIFY teamsChanged)
    Q_PROPERTY(QUrl baseURL READ getBaseURL WRITE setBaseURL NOTIFY baseURLChanged)
    Q_PROPERTY(quint16 messageCount READ getMessageCount WRITE setMessageCount NOTIFY messageCountChanged)
    Q_PROPERTY(quint16 mentionCount READ getMentionCount WRITE setMentionCount NOTIFY mentionCountChanged)
    Q_PROPERTY(QString state READ getState WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(MattermostFile* selectedFile READ getSelectedFile WRITE setSelectedFile NOTIFY selectedFileChanged)
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

    QUrl getBaseURL() const;
    void setBaseURL(const QUrl &value);

    QString getAuthorization();

    QString getNewMessage() const;
    void setNewMessage(const QString &value);

    quint16 getMessageCount() const;
    void setMessageCount(quint16 value);

    quint16 getMentionCount() const;
    void setMentionCount(quint16 value);

    QString getState() const;
    void setState(const QString &value);

    MattermostFile *getSelectedFile() const;
    void setSelectedFile(MattermostFile *value);

signals:
    void hostChanged(const QString& host);
    void usernameChanged(const QString& username);
    void passwordChanged(const QString& password);
    void selectedTeamChanged(const MattermostTeam* team);
    void teamsChanged();
    void baseURLChanged(const QUrl& value);
    void newMessageChanged(const QString& newMessage);
    void messageCountChanged(quint16 &value);
    void mentionCountChanged(quint16 &value);
    void stateChanged(QString &value);
    void selectedFileChanged(const MattermostFile* file);

public slots:
    void connectToHost();
    void disconnectFromHost();
    void refreshTeams();
    void refreshTeamUnreads();
    void refreshChannels(MattermostTeam* team);
    void refreshTeamMembers(MattermostTeam* team);
    void refreshUsers();
    void refreshChannelPosts(MattermostChannel* channel);
    void onResponse(QNetworkReply* reply);
    void onWebSocketConnected();
    void onWebSocketDisconnected();
    void onWebSocketMessage(QString message);
    void onWebSocketError(QAbstractSocket::SocketError error);
    void sendNewMessage(MattermostChannel* channel);
    void initFile(QString fileId);

private:
    QString host;
    QString username;
    QString password;
    QVariantMap user;
    QList<MattermostTeam*> teams;
    QMap<QString, MattermostUser*> users;

    MattermostTeam* selectedTeam;
    MattermostFile* selectedFile;
    QList<QString> loadingFileMetaIds;
    QString newMessage;
    quint16 messageCount;
    quint16 mentionCount;
    QString state;

    QUrl baseURL;
    QNetworkAccessManager* netAccessManager;
    QWebSocket* webSocket;
    quint64 webSocketSeq;
    QString token;

    MattermostTeam* findTeamById(QString teamId);
};

#endif // MATTERMOSTCLIENT_H
